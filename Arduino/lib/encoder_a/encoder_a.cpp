#include "encoder_a.h"
#include <std_msgs/Int16.h>

Encoder left(0,0); // temporary values
Encoder right(0,0); // temporary values

void Encoder_a::initEncoder(int l1, int l2, int r1, int r2) {
    left = Encoder(l1, l2);
    right = Encoder(r1, r2);
}

int Encoder_a::left_counter() {
  boolean leftDir = true;
  const int encoder_maximum = 32768;
  const int encoder_minimum = -32768;
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

  return tick_val;
}

int Encoder_a::right_counter(){
  boolean rightDir = true;
  const int encoder_maximum = 32768;
  const int encoder_minimum = -32768;
  int tick_val = right.read();
  static int pre_tick_valR = 0;

  // Checks in which direction the motor is moving
  if (tick_val != pre_tick_valR) {
    rightDir = (tick_val > pre_tick_valR) ? true : false;
  }
  if (rightDir) {
    if (tick_val == encoder_maximum) tick_val = encoder_minimum;
    else tick_val++;
  }
  else {
    if (tick_val == encoder_minimum) tick_val = encoder_maximum;
    else tick_val--;
  }
  pre_tick_valR = right.read();
  return tick_val;
}