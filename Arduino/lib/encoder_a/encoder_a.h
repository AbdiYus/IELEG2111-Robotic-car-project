#ifndef ENCODER_A_H   
#define ENCODER_A_H

#include "Arduino.h"
#include <Encoder.h>

extern Encoder left;
extern Encoder right;

namespace Encoder_a {
    int tick_counter(char side);
}
#endif