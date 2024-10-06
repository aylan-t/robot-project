/*
 * Nom: Aziz Maaref / Elias Dawiss / Aylan Tighilet / Nour Choubani
 * Equipe: 88102
 * Section:  4
 * Correcteur: Paul Petibon
 * Description: La classe permet de tester si le bouton est appuyé et configure uniquement l'interruption.

 * Identifications matérielles : PIND2
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

class Button
{
public:
    static const uint8_t DEBOUNCE_DELAY = 10;
    static const uint8_t MASK_D2 = (1 << PD2);
    static bool isPushed();
    static void initialize();
};

#endif // BUTTON_H