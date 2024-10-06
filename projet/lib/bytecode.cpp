#include "bytecode.h"
#include "debug.h"


Bytecode::Bytecode() 
{
    engine.initialization();
}

void Bytecode::instructionExec(uint8_t bytecode, uint8_t parameter, uint16_t& address){
    
    if (bytecode == DBT){
        startExec = true;
    }

    if (startExec){
        switch (bytecode) {
            case DBT:
                startSequence();
            case ATT:
                while (parameter){
                    _delay_ms(WAIT_TIME_MS);
                    parameter--;
                }                
                break;
            case DAL:
                switch (parameter) {
                    case 0:
                        break;
                    case 1:
                        // led.green();
                        break;
                    case 2:
                        // led.red();
                        break;
                }break;
            case DET:
                // led.off();
                break;
            case SGO:
                beeper.playNote(parameter);
                break;
            case SAR:
                beeper.soundOff();
                break;
            case MAR1:
            case MAR2:
                engine.turnedOff();
                break;
            case MAV:
                engine.goForward((parameter / 255) * 100);
                break;
            case MRE:
                engine.goBackward((parameter / 255) * 100);
                break;
            case TRD:
                engine.turnRight((parameter / 255) * 100);
                break;
            case TRG:
                engine.turnLeft((parameter / 255) * 100);
                break;
            case DBC:
                startLoop(parameter, address);
                break;
            case FBC:
                address = endLoop();
                break;
            case FIN:
                startExec = false;
                break;
        }
    }
}

void Bytecode::startLoop(uint8_t counter, const uint16_t address){
    loopAddress = address;
    loopCounter =  counter;
}

uint16_t Bytecode::endLoop(){
    if (loopCounter != 0){
        loopCounter--;
    }
    return loopAddress;
}

// uint8_t Bytecode::getAddress() const{
//     return adress;
// }

bool Bytecode::getStartExec() const{
    return startExec;
}

// void Bytecode::addressIncrement(){
//     adress++;
// }

void Bytecode::startSequence(){
    // led.red();
    // _delay_ms(50);
    // led.off();
    // _delay_ms(50);
    // led.red();
    // _delay_ms(50);
    // led.off();
    // _delay_ms(50);
    // led.green();
    // _delay_ms(50);
    // led.off();
    // _delay_ms(50);
    // led.green();
    // _delay_ms(50);
    // led.off();
    // _delay_ms(50);
}