/*
 * Nom: Aziz Maaref / Elias Dawiss / Aylan Tighilet / Nour Choubani
 * Equipe: 88102
 * Section:  4
 * Correcteur: Paul Petibon
 * Description: La classe permet de choisir le timer souhaité, avec un prescaler pour l'horloge. Elle permet l'utilisation des modes CTC
 * normal et pwm. Elle a une méthode pour partir et arrêter la minuterie

 * Identifications matérielles : dépend du timer choisi.
 */




#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>


#define F_CPU 8000000UL

class Timer {
public:
    
    Timer(uint8_t timerCounterNumber, uint16_t clockPrescaler);

    
    void assignRegisters(volatile uint8_t* tccrna, volatile uint8_t* tccrnb, volatile uint8_t* tcntn, volatile uint8_t* ocrna, volatile uint8_t* timskn, volatile uint8_t wgmn0, volatile uint8_t wgmn1, volatile uint8_t wgmn2, volatile uint8_t comna1, volatile uint8_t comna0, volatile uint8_t comnb1, volatile uint8_t comnb0);
    void start(uint16_t duration);
    void startMicroS(uint16_t duration);
    void stop();
    void setInterrupt(bool isEnabled);
    void setClockPrescaler(uint16_t prescaler);
    void setModeNormal();
    void setModeCTC();
    void setModePWM();
    void setModeFastPWM();

    
    const bool getIsStarted();
    const bool getInterruptIsEnabled();
    const uint16_t getClockPrescaler();

private:
    
    volatile uint8_t* TCCRnA;
    volatile uint8_t* TCCRnB;
    volatile uint8_t* TCNTn;
    volatile uint8_t* OCRnA;
    volatile uint8_t* TIMSKn;
    volatile uint8_t WGMn0;
    volatile uint8_t WGMn1;
    volatile uint8_t WGMn2;
    volatile uint8_t COMnA1;
    volatile uint8_t COMnA0;
    volatile uint8_t COMnB1;
    volatile uint8_t COMnB0;
    
    
    uint8_t timerNumber_;
    uint16_t clockPrescaler_;
    bool isStarted_;
    bool interruptIsEnabled_;
};

#endif // TIMER_H