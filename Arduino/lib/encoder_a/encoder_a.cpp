#include "encoder_a.h"
#include <std_msgs/Int16.h>

Encoder left(2, 4); 
Encoder right(19, 18); 

/**
*   Count the number of ticks from the encoder based on the direction
*   which is limited
* 
*   @param side - the side of the encoder
*/
int Encoder_a::tick_counter(char side) {
  boolean direction = true; // true = forward, false = backward
  const int encoder_maximum = 32768;
  const int encoder_minimum = -32768;
  static int pre_tick_val = 0;
  int tick_val = (side == 'l') ? left.read() : right.read();

  if (tick_val != pre_tick_val) {
    direction = (tick_val > pre_tick_val) ? true : false;
  }
  if (direction)  (tick_val == encoder_maximum ? encoder_minimum : tick_val++);
  else (tick_val == encoder_minimum ? encoder_maximum : tick_val--);

  pre_tick_val = (side == 'l') ? left.read() : right.read();
  return tick_val;
}