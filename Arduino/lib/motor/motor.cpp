#include "motor.h"
Servo m1;
Servo m2;

// verider : bak ((--) 80-180 (++)), fram ((++) 0-80 (--))

void Motor::initMotor(int pin1, int pin2) {
    m1.attach(pin1, 1000, 2000);
    m2.attach(pin2, 1000, 2000);
}

void Motor::forward() {
    m1.write(0);
    m2.write(0);
}

void Motor::backward() {
    m1.write(180);
    m2.write(180);
}

void Motor::turnRight() {
    m1.write(160);
    m2.write(20);  
}

void Motor::turnLeft() {
    m1.write(20);
    m2.write(160);  
}

void Motor::stop() {
  m1.write(80);
  m2.write(80);
}