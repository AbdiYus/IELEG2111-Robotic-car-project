#include "calculations.h"

/**
*   Calculate the velocity of the robot by using the encoder ticks
*
*   @param tick - the number of ticks from the encoder
*/
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

/**
*   Calculate the movement of the robot based on the velocity of the wheels
*
*   @param velR - the velocity of the right wheel
*   @param velL - the velocity of the left wheel
*   @param data - the message from the cmd_vel topic
*/
void Calculations::movement(double velR, double velL, geometry_msgs::Twist data) {
    int wheelSpeed = 0;
    int leftSpeed = 0;
    int rightSpeed = 0;

    if(data.angular.z != 0) { // if we are turning!
        leftSpeed = 25*data.angular.z + 80;
        rightSpeed = -25*data.angular.z + 80;
        if(data.angular.z > 0)  Motor::drive(leftSpeed, rightSpeed); // turn left
        else Motor::drive(leftSpeed, rightSpeed); // turn right 
    } else {
        wheelSpeed = 90*data.linear.x + 80; 
        if(data.linear.x > 0) Motor::drive(wheelSpeed, wheelSpeed); // go straight
        else Motor::drive(wheelSpeed, wheelSpeed); // go backwards
    }

    if(data.angular.z == 0 && data.linear.x == 0) Motor::drive(80, 80); // stop the robot
}