/*
 * Nom: Aziz Maaref / Elias Dawiss / Aylan Tighilet / Nour Choubani
 * Equipe: 88102
 * Section:  4
 * Correcteur: Paul Petibon
 * Description: Permet de controler la vitesse des roues et le changement de direction par l'utilisation du pwm.
    Elle configure les registres OCR1A et OCR1B en utilsant les pourcentages en parametres afin d'obtenir le duty cycle.

 * Identifications matérielles : Broches I/O ; PORTD4  et PORTD5 reliés à la broche E du pont en H (controle vitesse)// 
    PORTD6  et PORTD7 reliés à la broche D du pont en H (controle rotation moteur).
 */

#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>     



class Engine {
    public:

    Engine();
    void initialization();

    void setSpeed(uint8_t percentageWheelA, uint8_t percentageWheelB);
    void goForward(uint8_t percentageWheelA, uint8_t percentageWheelB);
    void goForward(uint8_t percentageWheels);
    void goBackward(uint8_t percentageWheels);
    void goBackward(uint8_t percentageWheelA, uint8_t percentageWheelB);
    void turnRight(uint8_t percentageWheelA);
    void turnLeft(uint8_t percentageWheelB);
    void turnedOff();

private:
    uint8_t percentageWheelA_ = 0; 
    uint8_t percentageWheelB_ = 0;

    static constexpr uint8_t TIMER_NUMBER = 1;
    static constexpr uint16_t CLOCK_PRESCALER = 8; 
    static constexpr uint8_t MAX_8_BITS = 255;
    static constexpr uint8_t CONVERSION_PERCENTAGE = 100;
};