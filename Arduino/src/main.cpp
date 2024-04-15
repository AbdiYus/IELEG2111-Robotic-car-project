#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif

#include <ros.h>

#include <std_msgs/Int16.h>
#include <std_msgs/Float32MultiArray.h>
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
void ps5(const std_msgs::Float32MultiArray &msg);
void publishTicks();
void move(const geometry_msgs::Twist &msg);


/*  ROS  */
ros::Subscriber<std_msgs::Int16> keyboard("keyboard", &key);
ros::Subscriber<std_msgs::Float32MultiArray> controller("controller", &ps5);
ros::Subscriber<geometry_msgs::Twist> cmd_vel("cmd_vel", &move);

std_msgs::Int16 right_tick; 
ros::Publisher rightPub("right_ticks", &right_tick);
std_msgs::Int16 left_tick; 
ros::Publisher leftPub("left_ticks", &left_tick);



void setup(){
  Motor::initMotor(11, 13);

  nh.initNode();
  nh.subscribe(keyboard);
  nh.subscribe(controller);
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
  if (msg.data == 1)  Motor::drive(0,0);   // up
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

/**
*   Move the robot based on the message from the ps5 topic
* 
*   @param msg - the message from the ps5 topic
*/
void ps5(const std_msgs::Float32MultiArray &msg) {
  if (msg.data[5] > 0.7) Motor::drive(0,0);   // up
  if (msg.data[2] > 0.7) Motor::drive(180,180);  // down
  if (msg.data[0] > 0.7) Motor::drive(160,20); // right
  if (msg.data[0] < -0.7) Motor::drive(20,160);   // left
}

/*
int leftSpeed = 80; 
    int rightSpeed = 80;

    // Forward and backward movement
    if (msg.data[5] > -1) { 
        int speed = -40 * msg.data[1] + 80; 
        leftSpeed = speed;
        rightSpeed = speed;
    } else if (msg.data[9] == 1) { 
        leftSpeed = 160; 
        rightSpeed = 160;
    }

    // Adjusting for turning
    if (msg.data[0] != 0) { 
        int turnAdjustment = 25 * msg.data[0]; 

        // Apply turn adjustment: Increase one side while decreasing the other
        leftSpeed -= turnAdjustment;
        rightSpeed += turnAdjustment;

        // Ensure motor speeds are within bounds
        leftSpeed = max(0, min(leftSpeed, 180));
        rightSpeed = max(0, min(rightSpeed, 180));
    }

    // Drive motors with calculated speeds
    Motor::drive(leftSpeed, rightSpeed);
*/