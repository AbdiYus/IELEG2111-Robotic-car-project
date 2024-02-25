#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int16.h>
#include "motor.h"
#include "encoder_a.h"

ros::NodeHandle  nh;

// delay
long prevTime = 0;
long currentTime = 0;
int interval = 100;

// ros 
void key(const std_msgs::Int16 &msg);
//void pos(const geometry_msgs::Twist &msg);

ros::Subscriber<std_msgs::Int16> keyboard("keyboard", &key);
//ros::Subscriber<geometry_msgs::Twist> cmd_vel("cmd_vel", &cmd);

std_msgs::Int16 right_tick; 
ros::Publisher rightPub("right_ticks", &right_tick);
std_msgs::Int16 left_tick; 
ros::Publisher leftPub("left_ticks", &left_tick);
void publishTicks();


void setup(){
  Motor::initMotor(11, 13);
  Encoder_a::initEncoder(19, 18, 2, 4);

  nh.initNode();
  nh.subscribe(keyboard);
 // nh.subscribe(cmd_vel);
  nh.advertise(leftPub);
  nh.advertise(rightPub);
}

void loop(){
  currentTime = millis();
  if(currentTime - prevTime > interval) {
    prevTime = currentTime;
    publishTicks();
    nh.spinOnce();
  }
}

// verider : bak ((--) 80-180 (++)), fram ((++) 0-80 (--))
void key(const std_msgs::Int16& msg) {
  if (msg.data == 1)  Motor::drive();   // up
  if (msg.data == 2)  Motor::drive(180,180);  // down
  if (msg.data == 3)  Motor::drive(160,20); // right
  if (msg.data == 4) Motor::drive(20,160);   // left
  if (msg.data == 0)  Motor::stop();
}

void publishTicks() {
  left_tick.data = Encoder_a::left_counter();
  right_tick.data = Encoder_a::right_counter();
  leftPub.publish(&left_tick);
  rightPub.publish(&right_tick);
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
