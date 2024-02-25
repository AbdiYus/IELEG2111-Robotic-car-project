#include "calculations.h"

double Calculations::velocity(int tick) {
    static double prevTime = 0;
    static int prevCount = 0; 
    double vel = 0;

    // roll-over/under fix 
    int numOfTicks = (65535 + tick - prevCount) % 65535;
    if(numOfTicks > 10000)  numOfTicks = -(65535 - numOfTicks); 

    // calculate velocity 
    vel = numOfTicks/1007/((millis()/1000)-prevTime); 
    prevCount = tick;
    return vel;
}

void Calculations::movement(double vel, geometry_msgs::Twist& cmdVel) {
    
}