#ifndef PARAMETER_H
#define PARAMETER_H

#include "mytime.h"

namespace par
{

// pins
const byte PUMP        = A0;
const byte VALVETOP    = A1;
const byte VALVEBOTTOM = A2;
const byte SWITCH      = 7;
const byte WATER       = 3;
const byte WATERLEVEL  = 4;
const byte MEASURE_WL  = 5;
const byte TEMPERATURE = 6;

// SD-pins
const byte CHIPSELECT = 10;  // SD-Card Pin for Arduino Uno

// Watering parameters for top plants
const float maxTemp                  = 55.0F;
const unsigned int timeMaxTempTop    = 60000;
const unsigned int timeMaxTempBottom = 55000;

const float temp4                  = 45.0F;
const unsigned int timeTemp4Top    = 40000;
const unsigned int timeTemp4Bottom = 25000;

const float temp3                  = 35.0F;
const unsigned int timeTemp3Top    = 30000;
const unsigned int timeTemp3Bottom = 25000;

const float temp2                  = 25.0F;
const unsigned int timeTemp2Top    = 17000;
const unsigned int timeTemp2Bottom = 14000;

const float lowTemp                  = 20.0F;
const unsigned int timeLowTempTop    = 10000;
const unsigned int timeLowTempBottom = 8000;

// Water Times
const TIME t1_water(11, 30, 0);
const TIME t2_water(15, 30, 0);
const byte t_valve            = 100;
const unsigned int t_half_can = 15000;
}  // namespace par

#endif