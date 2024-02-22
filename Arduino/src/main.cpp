/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif

#include <ros.h>
#include <std_msgs/Int16MultiArray.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int32.h>
#include <Encoder.h>
#include "motor.h"

ros::NodeHandle  nh;

// ecoder
Encoder left(19, 18);
Encoder right(2, 4);
long oldPositionL  = -999;
long oldPositionR  = -999;
long prevTime = 0;
long currentTime = 0;
int interval = 100;

// functions
int leftPos();
int rightPos();

// ros 
void key(const std_msgs::Int32 &msg);
void pos(const geometry_msgs::Twist &msg);

// Calculations
boolean leftDir = true;
boolean rightDir = true;
const int encoder_maximum = 32768;
const int encoder_minimum = -32768;



ros::Subscriber<std_msgs::Int32> keyboard("keyboard", &key);
//ros::Subscriber<geometry_msgs::Twist> cmd_vel("cmd_vel", &cmd);

std_msgs::Int16 right_tick; 
ros::Publisher rightPub("right_ticks", &right_tick);

std_msgs::Int16 left_tick; 
ros::Publisher leftPub("left_ticks", &left_tick);


void setup(){
  Motor::initMotor(11, 13);

  nh.initNode();
  nh.subscribe(keyboard);
 // nh.subscribe(cmd_vel);
  nh.advertise(leftPub);
  nh.advertise(rightPub);
}

void loop(){

  if(currentTime - prevTime > interval){
      prevTime = currentTime;
      rightPub.publish(&right_tick);
      leftPub.publish(&left_tick);
      nh.spinOnce();
   }

   
}

void left_tick_counter_function(){
  int tick_val = left.read();
  static int pre_tick_val = 0;

  // Checks in which direction the motor is moving
  if (tick_val != pre_tick_val) {
    leftDir = (tick_val > pre_tick_val) ? true : false;
  }
  if (leftDir) {
    if (tick_val == encoder_maximum) tick_val = encoder_minimum;
    else tick_val++;
  }
  else {
    if (tick_val == encoder_minimum) tick_val = encoder_maximum;
    else tick_val--;
  }
  pre_tick_val = left.read();

  std_msgs::Int16 left_tick;
  left_tick.data = tick_val;
  leftPub.publish(&left_tick); 
}

// int leftPos() {
//   long newPositionL = left.read();
//   if (newPositionL != oldPositionL) {
//     oldPositionL = newPositionL;
//   }
//   return oldPositionL; // Always return a value
// }

int rightPos() {
  long newPositionR = right.read();
  if (newPositionR != oldPositionR) {
    oldPositionR = newPositionR;
  }
  return oldPositionR; // Always return a value
}


// verider : bak ((--) 80-180 (++)), fram ((++) 0-80 (--))
void key(const std_msgs::Int32& msg) {
  if (msg.data == 1)  Motor::drive();   // up
  if (msg.data == 2)  Motor::drive(180,180);  // down
  if (msg.data == 3)  Motor::drive(160,20); // right
  if (msg.data == 4) Motor::drive(20,160);   // left
  if (msg.data == 0)  Motor::stop();
}


// void cmd(const geometry_msgs::Twist &msg) {
//   const float x = msg.linear.x;   
//   const float rotation = msg.linear.z;

//   if(x == 0 && rotation == 0) {
//     Motor::stop();
//     return;
//   }

//   if(rotation == 0) { // forward or backwards
//     (x > 0 ? Motor::forward() : Motor::backward());
//   }

//   if(x == 0) { // turn left or right
//     (rotation > 0 ? Motor::turnRight() : Motor::turnLeft());
//   }
// }