#ifndef ENCODER_A_H   
#define ENCODER_A_H

#include "Arduino.h"
#include <Encoder.h>

extern Encoder left;
extern Encoder right;

namespace Encoder_a {
    void initEncoder(int l1, int l2, int r1, int r2);
    int tick_counter(char side);
}
#endif