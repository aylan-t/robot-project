#include <avr/io.h>
#include "uart.h"

void Uart::initialize(void)
{
    // 2400 bauds. Nous vous donnons la valeur des deux premiers registres pour vous éviter des complications.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // Permettre la réception et la transmission par le UART0
    UCSR0A = (1 << UDRE0);
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
    // Format des trames: 8 bits (UCSZ01 et UCSZ00 à 1), 1 stop bits (USBS0 = 0) et sans parité (UPM00 et UPM01 à 0)
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void Uart::transmission(uint8_t donnee) // Du USART vers le PC
{
    // Copy pasted from p.174 of the ATmega documentation
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0))){
    } // UDRE0 = 1 quand le buffer est vide et qu'on peut écrire dans UDR0
    UDR0 = donnee; // On écrit dans UDR0 pour transmettre l'octet
}

void Uart::transmissionUnicode(uint8_t* donnee){
    uint8_t i =0;
    while (donnee[i] != '\0'){
        transmission(donnee[i++]);
    }
}

uint8_t Uart::reception()
{
    // Copy pasted from p.175 of the ATmega documentation
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0))){
    } // RXC0 = 1 quand il y a des données non lues dans UDR0
    return UDR0; // On lit UDR0 pour recevoir l'octet
}

