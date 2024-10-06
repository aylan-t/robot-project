#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "debug.h"
#include <string.h>
#include "robot.h"
#include "proxisensor.h"
#include "timer.h"


volatile bool timerDone = false;

ISR(TIMER1_COMPA_vect) {
}

ISR(TIMER0_COMPA_vect) {
    timerDone = true;
}

class CarrierIR {
    public:
        CarrierIR();

        Timer timer1 = Timer(1, 1);
        Timer timer0 = Timer(0, 1024);;

        void initialize();
        void sendLogicalOne();
        void sendLogicalZero();
        void intervalWait();
        void sendSIRCCommand(uint8_t command, uint8_t address);
};

CarrierIR::CarrierIR() {}

void CarrierIR::initialize() {
    DDRD |= (1 << DDD5);

    timer0.setModeCTC();
}

void CarrierIR::sendLogicalOne() {
    const uint8_t TIMER_PRESCALER = 1;
    const uint16_t CARRIER_FREQ = 38000; // 38kHz

    timer0.start(1200);

    while(!timerDone){
        timer1.setModePWM();
        OCR1A = (F_CPU / (2 * TIMER_PRESCALER * CARRIER_FREQ)) - 1;
    }
    
    timer1.stop();

}

void CarrierIR::sendLogicalZero() {
    const uint8_t TIMER_PRESCALER = 1;
    const uint16_t CARRIER_FREQ = 38000; // 38kHz

    timer0.start(600);

    while(!timerDone){
        timer1.setModePWM();
        OCR1A = (F_CPU / (2 * TIMER_PRESCALER * CARRIER_FREQ)) - 1;
    }
    
    timer1.stop();
    timer0.stop();

}

void CarrierIR::intervalWait() {

    timer0.start(600);

    while(!timerDone){
        PORTD &= ~(1 << PD5);
    }
    
    timer0.stop();

}

void CarrierIR::sendSIRCCommand(uint8_t address, uint8_t command) {
    // Envoyez le start bit, puis l'adresse et la commande
    // Implémentez ici la logique pour envoyer le start bit, l'adresse et la commande selon le protocole SIRC
}


class SensorIR {
    public:
        void initialize();
        void read();
        
};

void SensorIR::initialize() {
    DDRD |= (1 << PD5);
}

// uint8_t read() {
//     return IR_PIN & (1 << IR_INPUT_PIN2); // Lire la valeur de la broche PD2
// }

int main() 
{
    Robot robot;
    robot.initialize();

    CarrierIR sender;
    sender.initialize();

    while (true) {
        sender.sendLogicalOne();
        sender.intervalWait();
        sender.sendLogicalZero();
        
    }

    return 0;

}