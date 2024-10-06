/*
 * Nom: Aziz Maaref / Elias Dawiss / Aylan Tighilet / Nour Choubani
 * Equipe: 88102
 * Section:  4
 * Correcteur: Paul Petibon
 * Description: La classe permet de débogger par l'utilisation de usart.
 */

#include <avr/io.h>
#include "uart.h"
#include <string.h>
#include "memory_24.h"

constexpr uint8_t BUFFER_SIZE = 255;


void initDebug();
void printDebug(const char* str, ...);
void valueDebug(uint8_t value);
void value2(uint8_t value);
void largeValueDebug(uint16_t value);


#ifdef DEBUG
#define DEBUG_INIT() initDebug();
#define DEBUG_PRINT(...) printDebug(__VA_ARGS__)
#define DEBUG_VALUE(value) valueDebug(value);
#define DEBUG_VALUE2(value) value2(value);
#define DEBUG_LARGE_VALUE(value) largeValueDebug(value);

#else
 
#define DEBUG_INIT() {};
#define DEBUG_PRINT(str) {}; 
#define DEBUG_VALUE(value) {}; 
#define DEBUG_VALUE2(value) {};
#define DEBUG_LARGE_VALUE(value) {};

#endif 