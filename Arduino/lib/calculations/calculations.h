#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "Arduino.h"
#include "motor.h"
#include <geometry_msgs/Twist.h>

namespace Calculations {
    double velocity(int tick);
    void movement(double velR, double velL, geometry_msgs::Twist data);
}

#endif