#ifndef ROBOT_H
#define ROBOT_H

#include "robot.h"
#include "beeper.h"
#include "button.h"
#include "led.h"
#include "engine.h"
#include "timer.h"

// Créer la classe Robot

class Robot {
    public:
        Robot();

        Beeper beeper;
        Button button;
        Led led;
        Engine engine;
        Timer timer1 = Timer(1, 1024);

        void initialize();
};

#endif /* ROBOT_H */