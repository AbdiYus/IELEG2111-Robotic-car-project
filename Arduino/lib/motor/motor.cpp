#include "motor.h"
Servo m1;
Servo m2;

// verider : bak ((--) 80-180 (++)), fram ((++) 0-80 (--))

void Motor::initMotor(int pin1, int pin2) {
    m1.attach(pin1, 1000, 2000);
    m2.attach(pin2, 1000, 2000);
}


/**
*   This function let's you drive the car by setting the speed of the motors.
*   
*   Basic rules:
*   - 0 = full forward
*   - 180 = full backward
*   - 160 right 20 left = turn right
*   - 20 right 160 left = turn left
*   - 80 right 80 left = stop
*
*   @param right - speed of the right motor
*   @param left - speed of the left motor
*/
void Motor::drive(int right, int left) {
  m1.write(right);
  m2.write(left);
}

void Motor::stop() {
  m1.write(80);
  m2.write(80);
}