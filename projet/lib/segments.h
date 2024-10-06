#include "robot.h"
#include "beeper.h"
#include "button.h"
#include "led.h"
#include "engine.h"
#include "timer.h"

class Segment{
public:
    Segment()= default;
    Segment(uint8_t column, uint8_t line1,uint8_t line2): startingLine(line1), endLine(line2), columnPosition(column){};
    Segment(uint8_t distance, bool topLine, uint8_t segmentSize){
        uint8_t conversionPosition = distance / WIDTH_CONVERSION;
        if (topLine){
            columnPosition = START_COLUMN + conversionPosition;
            startingLine = 5;
            if (segmentSize == 4){endLine = startingLine + 3;}
            if (segmentSize == 6){endLine = startingLine + 4;}
            if (segmentSize == 8){endLine = startingLine + 5;}
        }
        else {
            columnPosition = END_COLUMN - conversionPosition;
            startingLine = 21;
            if (segmentSize == 4){endLine = startingLine - 3;}
            if (segmentSize == 6){endLine = startingLine - 4;}
            if (segmentSize == 8){endLine = startingLine - 5;}
        }
    }
    uint8_t startingLine = 0;
    uint8_t endLine = 0;
    uint8_t  columnPosition = 0;
    const uint8_t START_COLUMN = 41;
    const uint8_t END_COLUMN = 90;
    const double WIDTH_CONVERSION = 0.95; 


};