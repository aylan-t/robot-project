#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "debug.h"
#include "robot.h"
#include "uart.h"
#include "segments.h"


void affichageRobot1(Segment segments[], uint8_t size){
    Uart uart;
    uart.initialize();
    _delay_ms(5000);
    for (uint8_t lines = 0; lines < 27; lines++){
        for (uint8_t columns = 0; columns < 101; columns++){

            if(lines == 0){
                if (columns == 0){uart.transmissionUnicode((uint8_t*)"\u250C");}
                else if (columns == 100){uart.transmissionUnicode((uint8_t*)"\u2510");}
                else {uart.transmissionUnicode((uint8_t*)"\u2500");}
            }

            else if (lines == 3){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if(columns == 6){uart.transmissionUnicode((uint8_t*)"\u250F");}
                else if (columns == 31){uart.transmissionUnicode((uint8_t*)"\u2513");}
                else if (columns > 6 && columns < 31) {uart.transmissionUnicode((uint8_t*)"\u2501");}
                else {uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if ((lines > 3 && lines < 5)|| (lines > 21 && lines < 23)){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if(columns == 6 || columns == 31){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else {uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if( lines == 5){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 || columns == 31){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40){uart.transmissionUnicode((uint8_t*)"\u2554");}
                else if (columns == 91){uart.transmissionUnicode((uint8_t*)"\u2557");}
                else if (columns > 40 && columns < 91){ 
                    // on vas verifier les segments a acolumnsouter!
                    bool estAjouter = false;
                    for (int i = 0; i < size; i++)
                    {
                        if(lines == segments[i].startingLine){
                            if(segments[i].columnPosition == columns){
                                uart.transmissionUnicode((uint8_t*)"\u2566");
                                estAjouter = true;
                            }
                        }
                    }

                    if(!estAjouter){
                        uart.transmissionUnicode((uint8_t*)"\u2550");
                    }
                     
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if( lines > 5 && lines < 12){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 || columns == 31){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40 || columns == 91){uart.transmissionUnicode((uint8_t*)"\u2551");}
                else if (columns > 40 && columns < 91){
                    bool estAjouter = false;
                    for (int i = 0; i < size; i++)
                    {
                        if(5 == segments[i].startingLine){
                            if(segments[i].columnPosition == columns){
                                if (lines < segments[i].endLine){
                                    uart.transmissionUnicode((uint8_t*)"\u2551");
                                    estAjouter = true;
                                }
                            }
                        }
                    }

                    if(!estAjouter){
                        uart.transmissionUnicode((uint8_t*)" ");
                    }
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if( lines == 12){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 ){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40 || columns == 91){uart.transmissionUnicode((uint8_t*)"\u2551");}
                else if (columns > 40 && columns < 91){
                    // on vas verifier les segments a acolumnsouter!
                    // On fait rien pour le moment.
                    uart.transmissionUnicode((uint8_t*)" ");
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if( lines == 13){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 ){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40){uart.transmissionUnicode((uint8_t*)"\u2563");}
                else if (columns > 34 && columns < 40){uart.transmissionUnicode((uint8_t*)"\u2550");}
                else if (columns == 91){uart.transmissionUnicode((uint8_t*)"\u2551");}
                else if (columns > 40 && columns < 91){
                    // on vas verifier les segments a acolumnsouter!
                    // On fait rien pour le moment.
                    uart.transmissionUnicode((uint8_t*)" ");
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }

            else if( lines == 14){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 ){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40 || columns == 91){uart.transmissionUnicode((uint8_t*)"\u2551");}
                else if (columns > 40 && columns < 91){ 
                    // on vas verifier les segments a acolumnsouter!
                    // On fait rien pour le moment.
                    uart.transmissionUnicode((uint8_t*)" ");
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if( lines > 14 && lines < 21){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 || columns == 31){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40 || columns == 91){uart.transmissionUnicode((uint8_t*)"\u2551");}
                else if (columns > 40 && columns < 91){
                    bool estAjouter = false;
                    for (int i = 0; i < size; i++)
                    {
                        if(21 == segments[i].startingLine){
                            if(segments[i].columnPosition == columns){
                                if (lines > segments[i].endLine){
                                    uart.transmissionUnicode((uint8_t*)"\u2551");
                                    estAjouter = true;
                                }
                            }
                        }
                    }

                    if(!estAjouter){
                        uart.transmissionUnicode((uint8_t*)" ");
                    }
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if( lines == 21){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 || columns == 31){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40){uart.transmissionUnicode((uint8_t*)"\u255A");}
                else if (columns == 91){uart.transmissionUnicode((uint8_t*)"\u255D");}
                else if (columns > 40 && columns < 91){ 
                    bool estAjouter = false;
                    for (int i = 0; i < size; i++)
                    {
                        if(lines == segments[i].startingLine){
                            if(segments[i].columnPosition == columns){
                                uart.transmissionUnicode((uint8_t*)"\u2569");
                                estAjouter = true;
                            }
                        }
                    }

                    if(!estAjouter){
                        uart.transmissionUnicode((uint8_t*)"\u2550");
                    }
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if (lines == 23){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6){uart.transmissionUnicode((uint8_t*)"\u2517");}
                else if(columns == 31){uart.transmissionUnicode((uint8_t*)"\u251B");}
                else if (columns > 6 && columns < 31){uart.transmissionUnicode((uint8_t*)"\u2501");}
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if (lines == 26){
                if(columns == 0){uart.transmissionUnicode((uint8_t*)"\u2514");}
                else if (columns == 100){uart.transmissionUnicode((uint8_t*)"\u2518");}
                else {uart.transmissionUnicode((uint8_t*)"\u2500");}
            }

            else {
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            _delay_ms(5);
        }
        uart.transmissionUnicode((uint8_t*)"\n");
        _delay_ms(5);
    }
}

void affichageRobot2(Segment segments[], uint8_t size){
    Uart uart;
    uart.initialize();
    _delay_ms(5000);
    for (uint8_t lines = 0; lines < 27; lines++){
        for (uint8_t columns = 0; columns < 101; columns++){

            if(lines == 0){
                if (columns == 0){uart.transmissionUnicode((uint8_t*)"\u250C");}
                else if (columns == 100){uart.transmissionUnicode((uint8_t*)"\u2510");}
                else {uart.transmissionUnicode((uint8_t*)"\u2500");}
            }

            else if (lines == 3){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if(columns == 6){uart.transmissionUnicode((uint8_t*)"\u250F");}
                else if (columns == 31){uart.transmissionUnicode((uint8_t*)"\u2513");}
                else if (columns > 6 && columns < 31) {uart.transmissionUnicode((uint8_t*)"\u2501");}
                else {uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if ((lines > 3 && lines < 5)|| (lines > 21 && lines < 23)){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if(columns == 6 || columns == 31){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else {uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if( lines == 5){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 || columns == 31){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40){uart.transmissionUnicode((uint8_t*)"\u2554");}
                else if (columns == 91){uart.transmissionUnicode((uint8_t*)"\u2557");}
                else if (columns > 40 && columns < 91){ 
                    // on vas verifier les segments a acolumnsouter!
                    bool estAjouter = false;
                    for (int i = 0; i < size; i++)
                    {
                        if(lines == segments[i].startingLine){
                            if(segments[i].columnPosition == columns){
                                uart.transmissionUnicode((uint8_t*)"\u2566");
                                estAjouter = true;
                            }
                        }
                    }

                    if(!estAjouter){
                        uart.transmissionUnicode((uint8_t*)"\u2550");
                    }
                     
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if( lines > 5 && lines < 12){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 || columns == 31){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40 || columns == 91){uart.transmissionUnicode((uint8_t*)"\u2551");}
                else if (columns > 40 && columns < 91){
                    bool estAjouter = false;
                    for (int i = 0; i < size; i++)
                    {
                        if(5 == segments[i].startingLine){
                            if(segments[i].columnPosition == columns){
                                if (lines < segments[i].endLine){
                                    uart.transmissionUnicode((uint8_t*)"\u2551");
                                    estAjouter = true;
                                }
                            }
                        }
                    }

                    if(!estAjouter){
                        uart.transmissionUnicode((uint8_t*)" ");
                    }
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if( lines == 12){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 ){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40 || columns == 91){uart.transmissionUnicode((uint8_t*)"\u2551");}
                else if (columns > 40 && columns < 91){
                    // on vas verifier les segments a acolumnsouter!
                    // On fait rien pour le moment.
                    uart.transmissionUnicode((uint8_t*)" ");
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if( lines == 13){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 ){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40){uart.transmissionUnicode((uint8_t*)"\u2563");}
                else if (columns > 34 && columns < 40){uart.transmissionUnicode((uint8_t*)"\u2550");}
                else if (columns == 91){uart.transmissionUnicode((uint8_t*)"\u2551");}
                else if (columns > 40 && columns < 91){
                    // on vas verifier les segments a acolumnsouter!
                    // On fait rien pour le moment.
                    uart.transmissionUnicode((uint8_t*)" ");
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }

            else if( lines == 14){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 ){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40 || columns == 91){uart.transmissionUnicode((uint8_t*)"\u2551");}
                else if (columns > 40 && columns < 91){ 
                    // on vas verifier les segments a acolumnsouter!
                    // On fait rien pour le moment.
                    uart.transmissionUnicode((uint8_t*)" ");
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if( lines > 14 && lines < 21){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 || columns == 31){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40 || columns == 91){uart.transmissionUnicode((uint8_t*)"\u2551");}
                else if (columns > 40 && columns < 91){
                    bool estAjouter = false;
                    for (int i = 0; i < size; i++)
                    {
                        if(21 == segments[i].startingLine){
                            if(segments[i].columnPosition == columns){
                                if (lines > segments[i].endLine){
                                    uart.transmissionUnicode((uint8_t*)"\u2551");
                                    estAjouter = true;
                                }
                            }
                        }
                    }

                    if(!estAjouter){
                        uart.transmissionUnicode((uint8_t*)" ");
                    }
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if( lines == 21){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6 || columns == 31){uart.transmissionUnicode((uint8_t*)"\u2503");}
                else if (columns == 40){uart.transmissionUnicode((uint8_t*)"\u255A");}
                else if (columns == 91){uart.transmissionUnicode((uint8_t*)"\u255D");}
                else if (columns > 40 && columns < 91){ 
                    bool estAjouter = false;
                    for (int i = 0; i < size; i++)
                    {
                        if(lines == segments[i].startingLine){
                            if(segments[i].columnPosition == columns){
                                uart.transmissionUnicode((uint8_t*)"\u2569");
                                estAjouter = true;
                            }
                        }
                    }

                    if(!estAjouter){
                        uart.transmissionUnicode((uint8_t*)"\u2550");
                    }
                }
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if (lines == 23){
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else if (columns == 6){uart.transmissionUnicode((uint8_t*)"\u2517");}
                else if(columns == 31){uart.transmissionUnicode((uint8_t*)"\u251B");}
                else if (columns > 6 && columns < 31){uart.transmissionUnicode((uint8_t*)"\u2501");}
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            else if (lines == 26){
                if(columns == 0){uart.transmissionUnicode((uint8_t*)"\u2514");}
                else if (columns == 100){uart.transmissionUnicode((uint8_t*)"\u2518");}
                else {uart.transmissionUnicode((uint8_t*)"\u2500");}
            }

            else {
                if(columns == 0 || columns == 100){uart.transmissionUnicode((uint8_t*)"\u2502");}
                else{uart.transmissionUnicode((uint8_t*)" ");}
            }
            _delay_ms(5);
        }
        uart.transmissionUnicode((uint8_t*)"\n");
        _delay_ms(5);
    }
    uart.transmissionUnicode((uint8_t*)"Produit par: PolyTron");
}


int main()
{
    Segment segments[] = {Segment(9, true, 8),Segment(16, false, 4)};
    size_t size = sizeof(segments) / sizeof(segments[0]);
    affichageRobot1(segments, size);
    
}