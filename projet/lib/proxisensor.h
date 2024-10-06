#pragma once

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <string.h>
#include "robot.h"
#include "can.h"

class Proxisensor {
    public:
        Proxisensor();
        void initialize();
        uint8_t read();

        uint8_t capturedVoltage;

        can converter;
        
    private:
};