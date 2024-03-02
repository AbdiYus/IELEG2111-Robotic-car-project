#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif

#include <ros.h>

#include <std_msgs/Int16.h>
#include "motor.h"
#include "encoder_a.h"
#include "calculations.h"

ros::NodeHandle  nh;

/*  Delay  */
long prevTime = 0;
long currentTime = 0;
int interval = 100;

/*  Functions  */
void key(const std_msgs::Int16 &msg);
void publishTicks();
void move(const geometry_msgs::Twist &msg);


/*  ROS  */
ros::Subscriber<std_msgs::Int16> keyboard("keyboard", &key);
ros::Subscriber<geometry_msgs::Twist> cmd_vel("cmd_vel", &move);

std_msgs::Int16 right_tick; 
ros::Publisher rightPub("right_ticks", &right_tick);
std_msgs::Int16 left_tick; 
ros::Publisher leftPub("left_ticks", &left_tick);



void setup(){
  Motor::initMotor(11, 13);

  nh.initNode();
  nh.subscribe(keyboard);
  nh.subscribe(cmd_vel);
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

/**
*   Move the robot based on the message from the keyboard topic
*/
void key(const std_msgs::Int16& msg) {
  if (msg.data == 1)  Motor::drive();   // up
  if (msg.data == 2)  Motor::drive(180,180);  // down
  if (msg.data == 3)  Motor::drive(160,20); // right
  if (msg.data == 4) Motor::drive(20,160);   // left
  if (msg.data == 0)  Motor::stop();
}

/**
*   Publish the number of ticks from the encoders
*/
void publishTicks() {
  left_tick.data = Encoder_a::tick_counter('l');
  right_tick.data = Encoder_a::tick_counter('r');
  leftPub.publish(&left_tick);
  rightPub.publish(&right_tick);
}

/**
*   Move the robot based on the message from the cmd_vel topic
*
*   @param msg - the message from the cmd_vel topic
*/
void move(const geometry_msgs::Twist &msg) {
  double velR = Calculations::velocity(Encoder_a::tick_counter('r'));
  double velL = Calculations::velocity(Encoder_a::tick_counter('l'));
  Calculations::movement(velR, velL, msg);
}
