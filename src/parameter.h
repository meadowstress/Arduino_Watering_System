#ifndef PARAMETER_H
#define PARAMETER_H

#include "time.h"

namespace par
{

// pins
const short PUMP        = A0;
const short VALVETOP    = A1;
const short VALVEBOTTOM = A2;
const short SWITCH      = 7;
const short WATER       = 3;
const short WATERLEVEL  = 4;
const short MEASURE_WL  = 5;
const short TEMPERATURE = 6;

// SD-pins
const short CHIPSELECT = 10;  // SD-Card Pin for Arduino Uno

// Watering parameters for top plants
const float maxTemp                  = 55.0F;
const unsigned int timeMaxTempTop    = 60000;
const unsigned int timeMaxTempBottom = 10000;

const float temp4                  = 45.0F;
const unsigned int timeTemp4Top    = 40000;
const unsigned int timeTemp4Bottom = 8000;

const float temp3                  = 35.0F;
const unsigned int timeTemp3Top    = 30000;
const unsigned int timeTemp3Bottom = 5000;

const float temp2                  = 25.0F;
const unsigned int timeTemp2Top    = 15000;
const unsigned int timeTemp2Bottom = 4000;

const float lowTemp                  = 20.0F;
const unsigned int timeLowTempTop    = 8000;
const unsigned int timeLowTempBottom = 3000;

// Water Times
const TIME t1_water(11, 30);
const TIME t2_water(15, 30);
const unsigned int t_valve    = 100;
const unsigned int t_half_can = 15000;
}  // namespace par

#endif