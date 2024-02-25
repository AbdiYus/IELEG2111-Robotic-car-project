#include "encoder_a.h"
#include <std_msgs/Int16.h>

Encoder left(0,0); // temporary values
Encoder right(0,0); // temporary values

void Encoder_a::initEncoder(int l1, int l2, int r1, int r2) {
    left = Encoder(l1, l2);
    right = Encoder(r1, r2);
}

int Encoder_a::tick_counter(char side) {
  boolean direction = true; // true = forward, false = backward
  const int encoder_maximum = 32768;
  const int encoder_minimum = -32768;
  static int pre_tick_val = 0;
  int tick_val = (side == 'l') ? left.read() : right.read();

  if (tick_val != pre_tick_val) {
    direction = (tick_val > pre_tick_val) ? true : false;
  }
  if (direction)  tick_val = (tick_val == encoder_maximum ? encoder_minimum : tick_val + 1);
  else tick_val = (tick_val == encoder_minimum ? encoder_maximum : tick_val - 1);

  pre_tick_val = (side == 'l') ? left.read() : right.read();
  return tick_val;
}