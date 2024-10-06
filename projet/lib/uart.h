/*
 * Nom: Aziz Maaref / Elias Dawiss / Aylan Tighilet / Nour Choubani
 * Equipe: 88102
 * Section:  4
 * Correcteur: Paul Petibon
 * Description: La classe permet de transmettre des données du UART vers le pc par le protocole de communication RS232.
 * Identifications matérielles : Non applicable.
 */

#pragma once
#include <avr/io.h>
#include <string.h>



class Uart
{
public:
    Uart() = default;
    void initialize(void);
    void transmission(uint8_t donnee);
    void transmissionUnicode(uint8_t* donnee);
    uint8_t reception();
};
