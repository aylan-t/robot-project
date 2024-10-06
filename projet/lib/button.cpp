#include <avr/io.h>

#include "button.h"

bool Button::isPushed()
{
    if (PIND & MASK_D2)
    {
        _delay_ms(DEBOUNCE_DELAY);
        return (PIND & MASK_D2);
    }
    return false;
}

void Button::initialize()
{
    cli(); 
    DDRD &= ~(1 << DDD2); 
    EIMSK |= (1 << INT0);  
    EICRA |= (1 << ISC00);
    sei();
}         