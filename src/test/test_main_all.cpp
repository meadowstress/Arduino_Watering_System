#include <iostream>
#include <string>
#include <unistd.h>
#include <gtest/gtest.h>
#include "../time.h"
#include "../mock/mock_arduino.h"
#include "../PS_func.h"
#include "../parameter.h"

// include Tests
#include "test_Time.h"
#include "test_WaterSystem.h"
#include "test_mocks.h"

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