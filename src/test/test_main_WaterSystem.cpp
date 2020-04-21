#include <iostream>
#include <unistd.h>
#include <string>
#include <gtest/gtest.h>
#include "../time.h"
#include "../mock/mock_arduino.h"
#include "../PS_func.h"
#include "../parameter.h"
#include "test_WaterSystem.h"

const short PUMP = 8;
const short VALVETOP = 9;
const short VALVEBOTTOM = 10;
const short SWITCH = 7;
const short WATER = 3;
const short WATERLEVEL = 4;
const short MEASURE_WL = 5;
const short TEMPERATURE = 6;

bool pre_state_water = false;
bool current_state_water = false;
bool switch_on = false;
bool water_on = false;
bool timer_on = false;
bool water_level_ok = false;

DS3231 clock_var;
RTCDateTime DateTime;

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}