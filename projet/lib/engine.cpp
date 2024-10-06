#include <avr/io.h>
#include "timer.h"
#include "engine.h"
#include <util/delay.h>

Engine::Engine()
{
    DDRB |= (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5); 
}

void Engine::initialization()
{
    Timer timer0(0, 8); 
    timer0.setModePWM();
 
    setSpeed(0, 0);        
    
}
void Engine::setSpeed(uint8_t percentageWheelA, uint8_t percentageWheelB)
{
    percentageWheelA_ = percentageWheelA;
    percentageWheelB_ = percentageWheelB;

    OCR0A = (percentageWheelA_ * MAX_8_BITS) / CONVERSION_PERCENTAGE;
    OCR0B = (percentageWheelB_ * MAX_8_BITS) / CONVERSION_PERCENTAGE;
}

void Engine::goForward(uint8_t percentageWheelA, uint8_t percentageWheelB)
{
    setSpeed(percentageWheelA,percentageWheelB);
    PORTB &= ~(1 << PORTB2);
    PORTB &= ~(1 << PORTB5);
}

void Engine::goForward(uint8_t percentageWheels)
{
    setSpeed(percentageWheels,percentageWheels);
    PORTB &= ~(1 << PORTB2);
    PORTB &= ~(1 << PORTB5);
}
void Engine::goBackward(uint8_t percentageWheels)
{
    setSpeed(percentageWheels,percentageWheels);
    PORTB |= (1 << PORTB2);
    PORTB |= (1 << PORTB5);
}

void Engine::goBackward(uint8_t percentageWheelA, uint8_t percentageWheelB)
{
    setSpeed(percentageWheelA,percentageWheelB);
    PORTB |= (1 << PORTB2);
    PORTB |= (1 << PORTB5);
}

void Engine::turnLeft(uint8_t percentageWheelB)
{
    setSpeed(percentageWheelB,percentageWheelB);
    PORTB |= (1 << PORTB2);
    PORTB &= ~(1 << PORTB5);
}

void Engine::turnRight(uint8_t percentageWheelA)
{   
    setSpeed(percentageWheelA,percentageWheelA);
    PORTB &= ~(1 << PORTB2);
    PORTB |= (1 << PORTB5);
}
void Engine::turnedOff()
{
    setSpeed(0,0);
}