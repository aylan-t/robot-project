#include "led.h"

#define AMBER_DELAY 5


Led::Led(uint8_t redPin, uint8_t greenPin) : pinRed(redPin), pinGreen(greenPin) {
    DDRB |= (1 << pinRed) | (1 << pinGreen);
}

void Led::green() {
    PORTB &= ~(1 << pinRed);
    PORTB |= (1 << pinGreen);
}

void Led::red() {
    PORTB &= ~(1 << pinGreen);
    PORTB |= (1 << pinRed);
}

void Led::off() {
    PORTB &= ~((1 << pinRed) | (1 << pinGreen));
}

// Led::Led(volatile uint8_t& ddr, volatile uint8_t& port, uint8_t pinR, uint8_t pinG) 
//     : _ddr(ddr), _port(port), _pinR(pinR), _pinG(pinG) {
//     _ddr |= (1 << _pinR) | (1 << _pinG);
// }

// void Led::red() {
//     _port &= ~(1 << _pinG);
//     _port |= (1 << _pinR);
// }

// void Led::green() {
//     _port &= ~(1 << _pinR);
//     _port |= (1 << _pinG);
// }

// void Led::amber(uint8_t time) {
//     for (int i = 0; i < (120 * time); i++) {
//         red();
//         _delay_ms(AMBER_DELAY);
//         green();
//         _delay_ms(AMBER_DELAY);
//     }
// }

// void Led::off() {
//     _port &= ~((1 << _pinR) | (1 << _pinG));
// }
