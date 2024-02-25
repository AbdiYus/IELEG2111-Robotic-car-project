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

void Calculations::movement(double vel, geometry_msgs::Twist& data) {
    static long lastMessage = millis()/1000;

    if(data.angular.z != 0) { // if we are turning!
        if(data.angular.z > 0)  Motor::drive(20, 160); // turn left
        else Motor::drive(160, 20); // turn right 
    } else {
        
    }
}

// void calc_pwm_values(const geometry_msgs::Twist& cmdVel) {
//   // Go straight
//   else {
     
//     // Remove any differences in wheel velocities 
//     // to make sure the robot goes straight
//     static double prevDiff = 0;
//     static double prevPrevDiff = 0;
//     double currDifference = velLeftWheel - velRightWheel; 
//     double avgDifference = (prevDiff+prevPrevDiff+currDifference)/3;
//     prevPrevDiff = prevDiff;
//     prevDiff = currDifference;
 
//     // Correct PWM values of both wheels to make the vehicle go straight
//     pwmLeftReq -= (int)(avgDifference * DRIFT_MULTIPLIER);
//     pwmRightReq += (int)(avgDifference * DRIFT_MULTIPLIER);
//   }
 
//   // Handle low PWM values
//   if (abs(pwmLeftReq) < PWM_MIN) {
//     pwmLeftReq = 0;
//   }
//   if (abs(pwmRightReq) < PWM_MIN) {
//     pwmRightReq = 0;  
//   }  
// }