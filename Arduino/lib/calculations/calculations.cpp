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
    if(data.angular.z != 0) { // if we are turning!
        if(data.angular.z > 0)  Motor::drive(20, 160); // turn left
        else Motor::drive(160, 20); // turn right 
    } else {
        // remove differences in wheel velocities to make sure the robot goes straight
        // static double prevDiff = 0;
        // static double prevPrevDiff = 0;
        // double currDifference = velL - velR;
        // double avgDifference = (prevDiff+prevPrevDiff+currDifference)/3;
        // prevPrevDiff = prevDiff;
        // prevDiff = currDifference;

        // serial print the diffrence to check what is happening!!! TODO!!! 
        if(data.linear.x > 0) Motor::drive(160, 160); // go straight
        else Motor::drive(20, 20); // go backwards
    }

    if(data.angular.z == 0 && data.linear.x == 0) Motor::drive(0, 0); // stop the robot
}