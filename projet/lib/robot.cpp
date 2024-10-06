#include "robot.h"
#include "beeper.h"
#include "button.h"
#include "led.h"
#include "engine.h"
#include "timer.h"


Robot::Robot(): led(PB0, PB1) {}

void Robot::initialize() {
    engine.initialization();
    button.initialize();
    timer1.setModeCTC();

}