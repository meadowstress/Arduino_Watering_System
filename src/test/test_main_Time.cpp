#include <iostream>
#include <unistd.h>
#include <string>
#include <gtest/gtest.h>
#include "../time.h"
#include "../mock/mock_arduino.h"
#include "../PS_func.h"
#include "../parameter.h"
#include "test_Time.h"

bool pre_state_water     = false;
bool current_state_water = false;
bool switch_on           = false;
bool water_on            = false;
bool timer_on            = false;
bool water_level_ok      = false;

DS3231 clock_var;
RTCDateTime DateTime;

// global system variable
WaterSystem PumpControl;

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}