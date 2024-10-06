#pragma once
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "engine.h"
#include "beeper.h"

enum Actions
{
    DBT = 0x01, // début
    ATT = 0x02, // attendre
    DAL = 0x44, // allumer la DEL
    DET = 0x45, // éteindre la DEL
    SGO = 0x48, // jouer une sonorité
    SAR = 0x09, // arrêter de jouer la sonorité
    MAR1 = 0x60, // arrêter les moteurs
    MAR2 = 0x61, // arrêter les moteurs
    MAV = 0x62, // avancer
    MRE = 0x63, // reculer
    TRD = 0x64, // tourner à droite
    TRG = 0x65, // tourner à gauche
    DBC = 0xC0, // début de boucle
    FBC = 0xC1, // fin de boucle
    FIN = 0xFF  // fin
};

class Bytecode 
{
    public:

    static const uint8_t WAIT_TIME_MS = 25;
    
    Bytecode();

    void instructionExec(uint8_t bytecode, uint8_t parameter, uint16_t& address);

    void startLoop(uint8_t counter, const uint16_t address);

    uint16_t endLoop();

    // uint8_t getAddress() const;

    bool getStartExec() const;

    // void addressIncrement();

    void startSequence();

    private:
    Beeper beeper;
    Engine engine;
    bool startExec = false;
    // uint16_t adress = 0x00;
    uint16_t loopAddress = 0x00;
    uint8_t loopCounter = 0;

};


































