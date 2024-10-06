/*
 * Nom: Aziz Maaref / Elias Dawiss / Aylan Tighilet / Nour Choubani
 * Equipe: 88102
 * Section:  4
 * Correcteur: Paul Petibon
 * Description: La classe permet d'allumer la LED de différente couleur et de l'éteindre.

 * Identifications matérielles : PORTX0 ; PORTX1
 */

#ifndef LED_H
#define LED_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>


class Led {
private:
    uint8_t pinRed;
    uint8_t pinGreen;

public:
    Led(uint8_t redPin, uint8_t greenPin);

    void green();

    void red();

    void off();
};

#endif /* LED_H */



// public:
//     Led(volatile uint8_t& ddr, volatile uint8_t& port, uint8_t pinR, uint8_t pinG);
//     void red();
//     void green();
//     void amber(uint8_t time);
//     void off();

// private:
//     volatile uint8_t _ddr;
//     volatile uint8_t _port;
//     uint8_t _pinR;
//     uint8_t _pinG;
// };