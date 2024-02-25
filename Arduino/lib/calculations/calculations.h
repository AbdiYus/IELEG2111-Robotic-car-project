#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "Arduino.h"

namespace Calculations {
    int calculateSpeed(int tick, int prevTick, long prevTime, long currentTime);
    int calculateDistance(int tick, int prevTick);
}

#endif