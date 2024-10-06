#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "debug.h"
#include <string.h>
#include "robot.h"
#include "proxisensor.h"


volatile bool gIsButtonPressed = false;

const uint16_t TURN_DELAY = 2000;
const uint16_t TURN_DELAY_180 = 3500;
const uint8_t FULL_PERCENTAGE = 100;

enum class Etat
{
    SETUP, 
    WAIT, 
    RECEIVE,
    TRANSMIT
};

void testDebug()
{
    DEBUG_PRINT("Hello World");
    // DEBUG_VALUE(123);
    // DEBUG_LARGE_VALUE(12345);
}

ISR(INT0_vect) {
    gIsButtonPressed = true;
};

int main()
{
    testDebug();
    Robot robot;
    robot.initialize();

    Etat etat = Etat::SETUP;
    
    Proxisensor proxisensor;
    proxisensor.initialize();

    uint16_t sum = 0;
    double distance = 0.0;
    uint16_t transmission = 0;

    while (true)
    {
        switch (etat) {
            case Etat::SETUP:
                robot.led.green();
                for (uint8_t i = 0; i < 100; i++){
                    distance = static_cast<double>(proxisensor.read());
                    sum += distance;
                }
                distance = sum / 100;
                _delay_ms(3000);
                robot.led.off();
                DEBUG_VALUE2(distance);
                // if ((distance > 0x5f) | (distance < 0x10)) {
                //     etat = Etat::INIT;
                //     break;
                // }
                
                while (true){
                    robot.led.red();
                    if (distance > 0x31) {
                        robot.engine.goBackward(60, 68);
                        _delay_ms(10);
                        robot.engine.turnedOff();
                        robot.engine.goBackward(45, 50);
                        //robot.beeper.playNote(50);
                    } else if (distance < 0x30) {
                        robot.engine.goForward(60, 68);
                        _delay_ms(10);
                        robot.engine.turnedOff();
                        robot.engine.goForward(45, 50);
                        //robot.beeper.playNote(80);
                    } else {
                        break;
                    }
                    distance = static_cast<double>(proxisensor.read());
                }
                robot.led.green();
                robot.engine.turnedOff();
                _delay_ms(1500);

                distance = static_cast<double>(proxisensor.read());
                while (distance > 0x14) {
                    //robot.engine.turnRight(100);
                    //_delay_ms(10);
                    robot.engine.turnRight(52);
                    distance = static_cast<double>(proxisensor.read());
                }

                robot.engine.turnedOff();
                robot.led.red();

                

            case Etat::WAIT:
                robot.led.red();
                while (!gIsButtonPressed){

                }
                robot.beeper.tripleHighNote();
                etat = Etat::RECEIVE;
                break;
            
            // case Etat::RECEIVE:
            //     robot.led.off();


            //     break;
            
            // case Etat::TRANSMIT:
            //     robot.led.green();
            //     while (!gIsButtonPressed){

            //     }
            //     break;
        }
    }
            
    






    return 0;
}                                                                                                                   