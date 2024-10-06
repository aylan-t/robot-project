#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "debug.h"
#include <string.h>
#include "robot.h"
#include "uart.h"


volatile bool timerDone = false;
volatile uint16_t counter = 0;

bool inCircuit = true;

ISR(TIMER1_COMPA_vect) {
    timerDone = true;
    counter++;
}

enum LineState {
    UPPER_LINE,
    LOWER_LINE
};

struct Distance {
    uint8_t lenght;
    bool isSegment;
    LineState lineState;
};

constexpr uint8_t SEGMENT_LENGTH_1 = 8;
constexpr uint8_t SEGMENT_LENGTH_2 = 6;
constexpr uint8_t SEGMENT_LENGTH_3 = 4;

LineState currentLineState = UPPER_LINE;
const uint8_t MAX_DISTANCES = 14;
Distance distances[MAX_DISTANCES];
uint8_t numDistances = 0;
bool isSegment = false;
uint8_t numSegments = 0;

const uint8_t ONE_SECOND_TICKS = 20;

const double ROBOT_SPEED = 3.17;
const double ROBOT_WIDTH = 5.75;

const uint8_t VITESSE_MAX = 100;
const uint8_t VITESSE_NORMALE = 50;
const uint8_t VITESSE_TURN = 40;
const uint8_t VITESSE_MOYEN = 35;
const uint8_t VITESSE_LENT = 25;



uint8_t calculateSegmentLength(uint8_t counter) {
    if (counter > ONE_SECOND_TICKS) {
        DEBUG_PRINT(" Segment 8.5 added ");
        return SEGMENT_LENGTH_1;
    } else {
        DEBUG_PRINT(" Segment 6.5 added ");
        return SEGMENT_LENGTH_2;
    }
}

void addDistance(Distance *distances, const uint8_t &length, LineState lineState, uint8_t &numDistances) {
    if (numDistances < MAX_DISTANCES) {
        distances[numDistances].lenght = length;
        distances[numDistances].isSegment = isSegment;
        distances[numDistances].lineState = lineState;
        numDistances++;
        DEBUG_PRINT(" Distance added : %d ", length);
    }
}

void rightCornerSequence(Robot &robot) {
    DEBUG_PRINT(" Corner ");
    robot.engine.goForward(VITESSE_NORMALE);
    _delay_ms(830);
    robot.engine.turnedOff();
    _delay_ms(500);
    while(PINA) {
        robot.engine.turnRight(VITESSE_TURN);
    }
    robot.timer1.start(1900);
    DEBUG_PRINT(" Corner timer started ");
    while((PINA & 0b01000) == 0 && timerDone == 0) {
        robot.engine.turnRight(VITESSE_TURN);
    }
    robot.timer1.stop();
    robot.engine.turnLeft(VITESSE_TURN);
    _delay_ms(100);
    robot.engine.turnedOff();
    _delay_ms(500);
    if (timerDone){
        DEBUG_PRINT(" Corner Timer done ");
        addDistance(distances, SEGMENT_LENGTH_3, currentLineState, numDistances);
        DEBUG_PRINT(" Segment 4.5 added ");
        while((PINA & 0b00010) == 0){
            robot.engine.turnLeft(38);
            }
        robot.engine.turnRight(VITESSE_TURN);
        _delay_ms(100);
        }
    timerDone = false;
}

void demiTourSequence(Robot &robot) {
    DEBUG_PRINT(" RIEN ");
    robot.engine.turnedOff();
    _delay_ms(1000); 
    robot.engine.goForward(VITESSE_NORMALE);
    _delay_ms(1600); 
    robot.engine.turnedOff();
    _delay_ms(1500);
    DEBUG_PRINT(" Demi Tour ");
    while((PINA & 0b01000) == 0) {
            robot.engine.turnRight(VITESSE_TURN);
    }
    robot.engine.turnLeft(VITESSE_TURN);
    _delay_ms(200);
}

void leftCornerSequence(Robot &robot) {
    robot.engine.goForward(VITESSE_NORMALE);
    _delay_ms(300);
    if((PINA == 0b00000) || (PINA == 0b11111)){
        DEBUG_PRINT(" Corner Droite FROM GAUCHE LECTURE ");
        rightCornerSequence(robot);
    }
    else {
        DEBUG_PRINT(" Corner Gauche ");
        robot.engine.goForward(VITESSE_NORMALE, VITESSE_TURN);
        _delay_ms(800);
        robot.engine.turnedOff();
        _delay_ms(500);
        while(PINA){
            robot.engine.turnLeft(40);
        }
        while((PINA & 0b00010) == 0){
            robot.engine.turnLeft(38);
        }   
        robot.engine.turnedOff();
        inCircuit = false;
    }
}

void segmentSequence(Robot &robot) {
    DEBUG_PRINT(" Segment : ");
    robot.engine.goForward(VITESSE_NORMALE);
    _delay_ms(830); 
    robot.engine.turnedOff();
    _delay_ms(1000);
    while((PINA & 0b01000) == 0) {
            robot.engine.turnRight(VITESSE_TURN);
    }
    robot.engine.turnLeft(40);
    _delay_ms(100);
}

int main() {

    DEBUG_PRINT(" Starting ");

    Robot robot;
    robot.initialize();

    //sei();  // AJOUTER

    DDRA = 0x00;
    isSegment = false;

    while (inCircuit) {
        uint8_t SENSOR_VALUES = PINA;

        DEBUG_PRINT(" COUNTER IS %d ", counter);

        switch (SENSOR_VALUES) {
            case 0b11100:
                //DEBUG_PRINT("LE COUNTER EST %d\n", counter);
                timerDone = false;
                robot.timer1.stop();
                rightCornerSequence(robot);
                counter = 0;
                robot.timer1.start(100);
                break;
            case 0b11110:
                // DEBUG_PRINT("LE COUNTER EST %d\n", counter);
                robot.timer1.stop();
                timerDone = false;
                rightCornerSequence(robot);
                counter = 0;
                robot.timer1.start(100);
                break;
            case 0b10100:
                // DEBUG_PRINT("LE COUNTER EST %d\n", counter);
                robot.timer1.stop();
                timerDone = false;
                rightCornerSequence(robot);
                counter = 0;
                robot.timer1.start(100);
                break;
            case 0b10110:
                // DEBUG_PRINT("LE COUNTER EST %d\n", counter);
                robot.timer1.stop();
                timerDone = false;
                rightCornerSequence(robot);
                counter = 0;
                robot.timer1.start(100);
                break;
            case 0b00111:
                leftCornerSequence(robot); 
                break;
            case 0b01111:
                leftCornerSequence(robot);
                break;
            case 0b11111:
                timerDone = false;
                counter = 0;
                segmentSequence(robot);
                robot.timer1.start(100);
                break;
            case 0b00001:
                robot.engine.goForward(VITESSE_NORMALE, VITESSE_LENT);
                break;
            case 0b00011:
                robot.engine.goForward(VITESSE_NORMALE, VITESSE_LENT);
                break;
            case 0b00110:
                robot.engine.goForward(VITESSE_NORMALE, VITESSE_TURN);
                break;
            case 0b00010:
                robot.engine.goForward(VITESSE_NORMALE, VITESSE_MOYEN);
                break;
            case 0b00100:
                robot.engine.goForward(VITESSE_NORMALE);
                break;
            case 0b01100:
                robot.engine.goForward(VITESSE_TURN, VITESSE_NORMALE);
                break;
            case 0b01000:
                robot.engine.goForward(VITESSE_MOYEN, VITESSE_NORMALE);
                break;
            case 0b10000:
                robot.engine.goForward(VITESSE_LENT, VITESSE_NORMALE);
                break;
            case 0b11000:
                robot.engine.goForward(VITESSE_LENT, VITESSE_NORMALE);
                break;
            case 0b00000:
                _delay_ms(100);
                if(PINA){
                    DEBUG_PRINT(" false alarm ");
                    robot.timer1.stop();
                    timerDone = false;
                    rightCornerSequence(robot);
                    counter = 0;
                    robot.timer1.start(100);
                    break;
                }
                isSegment = true;
                uint8_t segmentLength = calculateSegmentLength(counter);
                addDistance(distances, segmentLength, currentLineState, numDistances);
                DEBUG_PRINT(" Segment added ");
                robot.timer1.stop();
                timerDone = false;
                counter = 0;
                demiTourSequence(robot);
                isSegment = false;
                break;
        }
    }
    return 0;
}
        // uint8_t lecture regle dans leftCornerSequence
                    // if (SENSOR_VALUES == 0b00111 || SENSOR_VALUES == 0b01111) {
                    //     DEBUG_PRINT("Second Read : \n");
                    //     _delay_ms(150);
                    //     if(PINA != 0b11111 && PINA != 0b00000){
                    //         SENSOR_VALUES = 0b00111;
                    //     } 
                    //     else {
                    //         SENSOR_VALUES = 0b11111;
                    //     }
                    // }