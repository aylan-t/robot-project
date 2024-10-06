#include <avr/io.h>
#define F_CPU 8000000UL

#include "timer.h"

Timer::Timer(uint8_t timerCounterNumber,uint16_t clockPrescaler){
    switch(timerCounterNumber) {
        case 0: 
            assignRegisters(&TCCR0A, &TCCR0B, &TCNT0, &OCR0A, &TIMSK0, WGM00, WGM01, WGM02, COM0A1, COM0A0, COM0B1, COM0B0);
            timerNumber_ = 0;
            break;
        case 1:
            assignRegisters(&TCCR1A, &TCCR1B, nullptr, nullptr, &TIMSK1, WGM10, WGM11, WGM12, COM1A1, COM1A0, COM1B1, COM1B0); 
            timerNumber_ = 1;
            break;
        case 2:
            assignRegisters(&TCCR2A, &TCCR2B, &TCNT2, &OCR2A, &TIMSK2, WGM20, WGM21, WGM22, COM2A1, COM2A0, COM2B1, COM2B0);
            timerNumber_ = 2;
            break;
    }

    clockPrescaler_ = clockPrescaler;
    setClockPrescaler(clockPrescaler_);
    isStarted_ = false;
    interruptIsEnabled_ = false;
}


void Timer::assignRegisters(volatile uint8_t* tccrna, volatile uint8_t* tccrnb, volatile uint8_t* tcntn, volatile uint8_t* ocrna, volatile uint8_t* timskn, volatile uint8_t wgmn0, volatile uint8_t wgmn1, volatile uint8_t wgmn2, volatile uint8_t comna1, volatile uint8_t comna0, volatile uint8_t comnb1, volatile uint8_t comnb0) {
    TCCRnA = tccrna;
    TCCRnB = tccrnb;
    TCNTn = tcntn;
    OCRnA = ocrna;
    TIMSKn = timskn;
    WGMn0 = wgmn0;
    WGMn1 = wgmn1;
    WGMn2 = wgmn2;
    COMnA1 = comna1;
    COMnA0 = comna0;
    COMnB1 = comnb1;
    COMnB0 = comnb0;
}

void Timer::setModeNormal() {
    *TCCRnA &= ~((1 << WGMn0)| (1 << WGMn1));
    *TCCRnA |= (1 << COMnA0);
    *TCCRnB |= ~(1 << WGMn2);

}

void Timer::setModeCTC() {
    *TCCRnA &= ~(1 << WGMn0) | ~(1 << WGMn1);
    *TCCRnB |= (1 << WGMn2);

}

void Timer::setModePWM() {

    *TCCRnA |= (1 << WGMn0) | (1 << COMnA1) | (1 << COMnB1);
    *TCCRnA &= ~(1 << WGMn1);
    *TCCRnB &= ~(1 << WGMn2);
    if(timerNumber_ == 1){
        TCNT1 = 0;
        TCCR1C = 0;  
    }
    else{
        *TCNTn = 0;
    }
}

void Timer::setModeFastPWM() {
    *TCCRnA |= (1 << WGMn0) | (1 << WGMn1);
    *TCCRnA |= (1 << WGMn2) | (1 << WGM13);

    
}


void Timer::start(uint16_t duration){
    setClockPrescaler(clockPrescaler_);
    const uint16_t msDivider = 1000;
    *TCCRnA |= (1 << COM1A1) | (1 << COM1A0);

    if(timerNumber_ == 1){
        TCCR1C = 0;
        TCNT1 = 0;                                      
        OCR1A = ((F_CPU/clockPrescaler_) * duration) / msDivider;
    }
    else{                                               
        *TCNTn = 0;
        *OCRnA = ((F_CPU/clockPrescaler_) * duration) / msDivider;
    }
    
    *TIMSKn |= (1 << OCIE1A);                            
    interruptIsEnabled_ = true;
    isStarted_ = true;
 
}

void Timer::startMicroS(uint16_t duration){
    setClockPrescaler(clockPrescaler_);
    const uint32_t microsDivider = 1000000;
    *TCCRnA |= (1 << COM1A1) | (1 << COM1A0);

    if(timerNumber_ == 1){
        TCCR1C = 0;
        TCNT1 = 0;
        OCR1A = ((F_CPU/clockPrescaler_) * duration) / microsDivider;
    }
    else{
        *TCNTn = 0;
        *OCRnA = ((F_CPU/clockPrescaler_) * duration) / microsDivider;
    }
    
    *TIMSKn |= (1 << OCIE1A);                            
    interruptIsEnabled_ = true;
    isStarted_ = true;
 
}

void Timer::stop(){
    *TCCRnB &= ~((1 << CS10) | (1 << CS11) | (1 << CS12)); 
    *TCCRnA &= ~((1 << COM1A1) | (1 << COM1A0));
    
    if(timerNumber_ == 1){
        TCCR1C = 0;
        TCNT1 = 0;                                      
        OCR1A = 0;
    }
    else{                                               
        *TCNTn = 0;
        *OCRnA = 0;
    }
    isStarted_ = false;
    *TIMSKn &= ~(1 << OCIE1A);


}

void Timer::setInterrupt(bool isEnabled){
    if(isEnabled){
        *TIMSKn |= (1 << OCIE1A);
        interruptIsEnabled_ = true;
    }
    else {
        *TIMSKn &= ~(1 << OCIE1A);
        interruptIsEnabled_ = false;
    }
}


void Timer::setClockPrescaler(uint16_t prescaler) {
    clockPrescaler_ = prescaler;
    uint8_t csBits = 0;
    switch(prescaler) {
        case 1: csBits = (1 << CS10); break;
        case 8: csBits = (1 << CS11); break;
        case 64: csBits = (1 << CS10) | (1 << CS11); break;
        case 256: csBits = (1 << CS12); break;
        case 1024: csBits = (1 << CS10) | (1 << CS12); break;
    }

    *TCCRnB &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
    *TCCRnB |= csBits;
}

const bool Timer::getIsStarted(){
    return isStarted_;
}

const bool Timer::getInterruptIsEnabled(){
    return interruptIsEnabled_;
}

const uint16_t Timer::getClockPrescaler(){
    return clockPrescaler_;
}
