#include <avr/io.h>
#include "timer.h"
#include "beeper.h"
#include <util/delay.h>
#include "debug.h"
#include "timer.h"



Beeper::Beeper() : frequency_(0), prescaler_(256) {
    DDRD |= (1 << DDD6) | (1 << DDD7);
}


void Beeper::soundOff(){
     TCCR0A = 0;
}

void Beeper::playNote(uint8_t note){

    timer2.setModeNormal();

    switch (note) {
        case 45: frequency_ = 110; break;
        case 46: frequency_ = 117; break;
        case 47: frequency_ = 123; break;
        case 48: frequency_ = 131; break;
        case 49: frequency_ = 139; break;
        case 50: frequency_ = 156; break;
        case 52: frequency_ = 165; break;
        case 53: frequency_ = 175; break;
        case 54: frequency_ = 185; break;
        case 55: frequency_ = 196; break;
        case 56: frequency_ = 208; break;
        case 57: frequency_ = 220; break;
        case 58: frequency_ = 233; break;
        case 59: frequency_ = 247; break;
        case 60: frequency_ = 262; break;
        case 61: frequency_ = 277; break;
        case 62: frequency_ = 294; break;
        case 63: frequency_ = 311; break;
        case 64: frequency_ = 330; break;
        case 65: frequency_ = 349; break;
        case 66: frequency_ = 370; break;
        case 67: frequency_ = 392; break;
        case 68: frequency_ = 415; break;
        case 69: frequency_ = 440; break;
        case 70: frequency_ = 466; break;
        case 71: frequency_ = 494; break;
        case 72: frequency_ = 523; break;
        case 73: frequency_ = 554; break;
        case 74: frequency_ = 587; break;
        case 75: frequency_ = 622; break;
        case 76: frequency_ = 659; break;
        case 77: frequency_ = 698; break;
        case 78: frequency_ = 740; break;
        case 79: frequency_ = 784; break;
        case 80: frequency_ = 831; break;
        case 81: frequency_ = 880; break;
    }
    
    OCR2A = (F_CPU/(2*prescaler_*frequency_)) - 1;
    
}


void Beeper::tripleHighNote(){
    this->playNote(45);
    _delay_ms(50);
    this->soundOff();
    _delay_ms(50);
    this->playNote(46);
    _delay_ms(50);
    this->soundOff();
    _delay_ms(50);
    this->playNote(47);
    _delay_ms(50);
    this->soundOff();
}



















