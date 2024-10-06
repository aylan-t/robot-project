# include "debug.h"
# include <stdlib.h>
# include <stdio.h>
// #include <cstdarg>

void initDebug()
{
    Uart uart = Uart();
    uart.initialize();
}

void printDebug(const char* str, ...)
{
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, str);
    vsnprintf(buffer, BUFFER_SIZE, str, args);
    va_end(args);

    Uart uart = Uart();
    uart.initialize();
    char* string = buffer;
    while(*string){
        uart.transmission(*string);
        string++;
    }
    uart.transmission('\n');

}

void valueDebug(uint8_t value)
{
    char buffer[4];
    itoa(value, buffer, BUFFER_SIZE);
    printDebug(buffer);
}

void value2(uint8_t value){
    Uart uart = Uart();
    uart.transmission(value);
}

void largeValueDebug(uint16_t value)
{
    char buffer[8];
    itoa(value, buffer, BUFFER_SIZE);
    printDebug(buffer);
}