#include "proxisensor.h"

Proxisensor::Proxisensor() {}

void Proxisensor::initialize()
{
    cli();

    DDRA &= ~(1 << PA0);

    sei();
}

uint8_t Proxisensor::read()
{
    uint8_t capturedVoltage = 0;

    capturedVoltage = static_cast<uint8_t>(converter.lecture(PA0) >> 2);

    return capturedVoltage;
}