#pragma once
#define F_CPU 8000000UL
#include <avr/io.h> 
#include "timer.h"



class Beeper {
    public:

    Beeper();
    void soundOff();
    void playNote(uint8_t note);
    void tripleHighNote();
    Timer timer2 = Timer(2, prescaler_);

    private:
    uint32_t frequency_;
    uint16_t prescaler_;

};























