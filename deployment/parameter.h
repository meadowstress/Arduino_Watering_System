#ifndef PARAMETER_H
#define PARAMETER_H

#include "time.h"

namespace par
{
    //Watering parameters for top plants
    const float maxTemp = 55.0F;
    const unsigned int timeMaxTempTop = 60000;
    const unsigned int timeMaxTempBottom = 20000;

    const float temp2 = 45.0F;
    const unsigned int timeTemp2Top = 40000;
    const unsigned int timeTemp2Bottom = 15000;

    const float temp3 = 35.0F;
    const unsigned int timeTemp3Top = 30000;
    const unsigned int timeTemp3Bottom = 10000;

    const float temp4 = 25.0F;
    const unsigned int timeTemp4Top = 20000;
    const unsigned int timeTemp4Bottom = 8000;

    const float lowTemp = 18.0F;
    const unsigned int timeLowTempTop = 8000;
    const unsigned int timeLowTempBottom = 4000;

    //Water Times
    const TIME t1_water(21,15);
    const TIME t2_water(21,17);
    const unsigned int t_valve = 100;
    const unsigned int t_half_can = 15000;
}

#endif