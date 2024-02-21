#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
#include <Servo.h>

extern Servo m1;
extern Servo m2;

namespace Motor {
    void initMotor(int pin1, int pin2);
    void forward();
    void backward();
    void turnRight();
    void turnLeft();
    void stop();
}

#endif