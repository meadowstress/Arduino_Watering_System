#include <iostream>
#include <string>
#include <unistd.h>
#include <gtest/gtest.h>
#include "time.h"
#include "mock_arduino.h"
#include "PS_func.h"
#include "parameter.h"

class WaterSystemTest : public ::testing::Test
{
 protected:
    void SetUp()
    {
        // code here will execute just before the test ensues
    }

    void TearDown()
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    // put in any custom data members that you need
    WaterSystem PS_;
};

TEST_F(WaterSystemTest, PS_func_readTemperature)
{
    PS_.updateTemperature();
    ASSERT_FLOAT_EQ(PS_.getTemperature(), 20.0F);
}

TEST_F(WaterSystemTest, PS_func_isSystemSwitchedOnTrue)
{
    switch_state = true;
    ASSERT_TRUE(PS_.isSystemSwitchedOn());
}

TEST_F(WaterSystemTest, PS_func_isSystemSwitchedOnFalse)
{
    switch_state = false;
    ASSERT_FALSE(PS_.isSystemSwitchedOn());
}

struct WaterActivationStates
{
    string title;
    bool pre_state_water;
    bool current_state_water;
    bool water_state;
    bool result;
};

class WaterActivationTest
    : public WaterSystemTest,
      public ::testing::WithParamInterface<WaterActivationStates>
{};

TEST_P(WaterActivationTest, WaterActivationStateTest)
{
    cout << endl << GetParam().title << endl;
    pre_state_water     = GetParam().pre_state_water;
    current_state_water = GetParam().current_state_water;
    water_state         = GetParam().water_state;
    ASSERT_EQ(PS_.isWaterActivated(), GetParam().result);
}

const WaterActivationStates TestVectorWaterActivationStates[] = {
    {"PARAMETER TEST: PS_func_isWaterActivatedTrueFF", false, false, true,
     true},
    {"PARAMETER TEST: PS_func_isWaterActivatedFalseFF", false, false, false,
     false},
    {"PARAMETER TEST: isWaterActivatedTrueTT", true, true, false, true},
    {"PARAMETER TEST: isWaterActivatedFalseTT", true, true, true, false}};

INSTANTIATE_TEST_SUITE_P(WaterActivationTest_PARAMETER,
                         WaterActivationTest,
                         testing::ValuesIn(TestVectorWaterActivationStates));

TEST_F(WaterSystemTest, HoldStateSwitchOn)
{
    switch_state       = true;
    water_level_state  = true;
    measure_current_wl = true;
    ASSERT_TRUE(PS_.holdState(3000));
}

TEST_F(WaterSystemTest, HoldStateSwitchOff)
{
    switch_state       = false;
    water_level_state  = true;
    measure_current_wl = true;
    ASSERT_FALSE(PS_.holdState(3000));
}

TEST_F(WaterSystemTest, PumpWaterSwitchOn)
{
    unsigned long pump_time  = par::t_half_can;
    unsigned short valve_pin = par::VALVETOP;
    unsigned long valve_time = par::t_valve;

    water_level_state = true;
    switch_state      = true;

    ASSERT_EQ(PS_.pumpWater(pump_time, valve_pin, valve_time), 1);
}

TEST_F(WaterSystemTest, PumpWaterSwitchOff)
{
    unsigned long pump_time  = par::t_half_can;
    unsigned short valve_pin = par::VALVETOP;
    unsigned long valve_time = par::t_valve;
    int result               = 0;

    water_level_state = true;
    switch_state      = false;

    result = PS_.pumpWater(pump_time, valve_pin, valve_time);
    ASSERT_EQ(result, 0);
}

TEST_F(WaterSystemTest, PumpWaterManual)
{
    // true-true-true
    int result = 0;
    // Waterlevel ok
    water_level_state  = true;
    measure_current_wl = true;

    // condition for switch enabled
    water_state     = true;
    pre_state_water = false;

    // On switch activated
    switch_state = true;

    result = PS_.pumpWaterManual();
    ASSERT_EQ(result, 1);

    // true-true-false
    result             = 0;
    water_level_state  = true;
    measure_current_wl = true;

    water_state     = true;
    pre_state_water = false;

    switch_state = false;

    result = PS_.pumpWaterManual();
    ASSERT_EQ(result, 0);

    // true-false-true
    result             = 0;
    water_level_state  = true;
    measure_current_wl = true;

    water_state     = true;
    pre_state_water = true;

    switch_state = true;

    result = PS_.pumpWaterManual();
    ASSERT_EQ(result, 0);

    // false-true-true
    result             = 0;
    water_level_state  = false;
    measure_current_wl = false;

    water_state     = true;
    pre_state_water = false;

    switch_state = true;

    result = PS_.pumpWaterManual();
    ASSERT_EQ(result, 0);

    // false-false-true
    result             = 0;
    water_level_state  = false;
    measure_current_wl = true;

    water_state     = true;
    pre_state_water = true;

    switch_state = true;

    result = PS_.pumpWaterManual();
    ASSERT_EQ(result, 0);

    // true-false-false
    result             = 0;
    water_level_state  = true;
    measure_current_wl = true;

    water_state     = true;
    pre_state_water = true;

    switch_state = false;

    result = PS_.pumpWaterManual();
    ASSERT_EQ(result, 0);

    // false-false-false
    result             = 0;
    water_level_state  = false;
    measure_current_wl = true;

    water_state     = true;
    pre_state_water = true;

    switch_state = false;

    result = PS_.pumpWaterManual();
    ASSERT_EQ(result, 0);
}

// Parameter test for Temperature Ranges of top plants
struct TemperatureRange
{
    string title;
    float temperature_value;
    float temperature_value_inc;
    unsigned int time;
};

class TemperatureRangeTestTop
    : public WaterSystemTest,
      public ::testing::WithParamInterface<TemperatureRange>
{};

TEST_P(TemperatureRangeTestTop, TemperatureRangeTestTop)
{
    cout << endl << GetParam().title << endl;
    temperature_value = GetParam().temperature_value;
    ASSERT_EQ(PS_.getWaterTimeTop(), GetParam().time);
    temperature_value = GetParam().temperature_value_inc;
    ASSERT_EQ(PS_.getWaterTimeTop(), GetParam().time);
}

const TemperatureRange TestVectorTemperatureRangeTop[] = {
    {"PARAMETER TEST: timeMaxTempTop", par::maxTemp, (par::maxTemp + 1.0F),
     par::timeMaxTempTop},
    {"PARAMETER TEST: timeTemp4Top", par::temp4, (par::temp4 + 1.0F),
     par::timeTemp4Top},
    {"PARAMETER TEST: timeTemp3Top", par::temp3, (par::temp3 + 1.0F),
     par::timeTemp3Top},
    {"PARAMETER TEST: timeTemp2Top", par::temp2, (par::temp2 + 1.0F),
     par::timeTemp2Top},
    {"PARAMETER TEST: timeLowTempTop", par::lowTemp, (par::lowTemp + 1.0F),
     par::timeLowTempTop},
    {"PARAMETER TEST: belowLowTempTop", 0.0F, (par::lowTemp - 1.0F), 0U}};

INSTANTIATE_TEST_SUITE_P(TemperatureRangeTestTop_PARAMETER,
                         TemperatureRangeTestTop,
                         testing::ValuesIn(TestVectorTemperatureRangeTop));

// Parameter test for Temperature Ranges of top plants

class TemperatureRangeTestBottom
    : public WaterSystemTest,
      public ::testing::WithParamInterface<TemperatureRange>
{};

TEST_P(TemperatureRangeTestBottom, TemperatureRangeTestBottom)
{
    temperature_value = GetParam().temperature_value;

    ASSERT_EQ(PS_.getWaterTimeBottom(), GetParam().time);

    temperature_value = GetParam().temperature_value_inc;

    ASSERT_EQ(PS_.getWaterTimeBottom(), GetParam().time);
}

const TemperatureRange TestVectorTemperatureRangeBottom[] = {
    {"PARAMETER TEST: timeMaxTempBottom", par::maxTemp, (par::maxTemp + 1.0F),
     par::timeMaxTempBottom},
    {"PARAMETER TEST: timeTemp4Bottom", par::temp4, (par::temp4 + 1.0F),
     par::timeTemp4Bottom},
    {"PARAMETER TEST: timeTemp3Bottom", par::temp3, (par::temp3 + 1.0F),
     par::timeTemp3Bottom},
    {"PARAMETER TEST: timeTemp2Bottom", par::temp2, (par::temp2 + 1.0F),
     par::timeTemp2Bottom},
    {"PARAMETER TEST: lowTempBottom", par::lowTemp, (par::lowTemp + 1.0F),
     par::timeLowTempBottom},
    {"PARAMETER TEST: belowLowTempBottom", 0.0F, (par::lowTemp - 1.0F), 0U}};

INSTANTIATE_TEST_SUITE_P(TemperatureRangeTestBottom_PARAMETER,
                         TemperatureRangeTestBottom,
                         testing::ValuesIn(TestVectorTemperatureRangeBottom));

TEST_F(WaterSystemTest, WateringEnabledTrue)
{
    temperature_value = 18.0F;
    ASSERT_TRUE(PS_.isAutomaticWateringEnabled());
    temperature_value = 20.0F;
    ASSERT_TRUE(PS_.isAutomaticWateringEnabled());
}

TEST_F(WaterSystemTest, isWateringEnabledFalse)
{
    temperature_value = 0.0F;
    ASSERT_FALSE(PS_.isAutomaticWateringEnabled());
    temperature_value = 5.0F;
    ASSERT_FALSE(PS_.isAutomaticWateringEnabled());
}

TEST_F(WaterSystemTest, isWaterLevelOk)
{
    water_level_state  = true;
    measure_current_wl = true;
    ASSERT_TRUE(PS_.isWaterLevelOk());

    water_level_state  = true;
    measure_current_wl = false;
    ASSERT_TRUE(PS_.isWaterLevelOk());

    water_level_state  = false;
    measure_current_wl = true;
    ASSERT_FALSE(PS_.isWaterLevelOk());

    water_level_state  = false;
    measure_current_wl = false;
    ASSERT_FALSE(PS_.isWaterLevelOk());
}

TEST_F(WaterSystemTest, Pump_Water_Clock_watering_true_t1)
{
    temperature_value = 20.0F;
    switch_state      = true;

    water_level_state  = true;
    measure_current_wl = true;

    current_local_time.hour   = 11;
    current_local_time.minute = 30;
    ASSERT_EQ(PS_.pumpWaterClock(), 2);
}

TEST_F(WaterSystemTest, Pump_Water_Clock_watering_true_t2)
{
    temperature_value = 20.0F;
    switch_state      = true;

    water_level_state  = true;
    measure_current_wl = true;

    current_local_time.hour   = 15;
    current_local_time.minute = 30;
    ASSERT_EQ(PS_.pumpWaterClock(), 2);
}

TEST_F(WaterSystemTest, Pump_Water_Clock_watering_false)
{
    temperature_value = 20.0F;
    switch_state      = true;

    water_level_state  = true;
    measure_current_wl = true;

    current_local_time.hour   = 10;
    current_local_time.minute = 30;
    ASSERT_EQ(PS_.pumpWaterClock(), 0);

    current_local_time.hour   = 12;
    current_local_time.minute = 30;
    ASSERT_EQ(PS_.pumpWaterClock(), 0);

    current_local_time.hour   = 14;
    current_local_time.minute = 30;
    ASSERT_EQ(PS_.pumpWaterClock(), 0);

    current_local_time.hour   = 16;
    current_local_time.minute = 30;
    ASSERT_EQ(PS_.pumpWaterClock(), 0);

    current_local_time.hour   = 0;
    current_local_time.minute = 0;
    ASSERT_EQ(PS_.pumpWaterClock(), 0);
}

TEST_F(WaterSystemTest, Pump_Water_Clock_switch_off)
{
    temperature_value = 20.0F;
    switch_state      = false;

    current_local_time.hour   = 11;
    current_local_time.minute = 30;
    ASSERT_EQ(PS_.pumpWaterClock(), 0);
}

TEST_F(WaterSystemTest, Pump_Water_Clock_low_temperature)
{
    temperature_value = 16.0F;
    switch_state      = true;

    current_local_time.hour   = 11;
    current_local_time.minute = 30;
    ASSERT_EQ(PS_.pumpWaterClock(), 0);
}

TEST_F(WaterSystemTest, systemTime_getLocalTime)
{
    TIME t(0, 0, 0);

    temperature_value = 20.0F;
    switch_state      = true;

    current_local_time.hour   = 15;
    current_local_time.minute = 13;

    t = PS_.getCurrentLocalTime();
    ASSERT_EQ(t.get_H(), 15);
    ASSERT_EQ(t.get_Min(), 13);
}

TEST_F(WaterSystemTest, isLoggingIntervallPassed)
{
    global_counter = 2000;

    ASSERT_FALSE(PS_.isLoggingIntervallPassed());

    global_counter = 1999;

    ASSERT_FALSE(PS_.isLoggingIntervallPassed());

    global_counter = 2001;

    ASSERT_FALSE(PS_.isLoggingIntervallPassed());

    global_counter = 3999;

    ASSERT_FALSE(PS_.isLoggingIntervallPassed());

    global_counter = 4000;

    ASSERT_TRUE(PS_.isLoggingIntervallPassed());

    global_counter = 4001;

    ASSERT_FALSE(PS_.isLoggingIntervallPassed());

    global_counter = 1234;

    ASSERT_FALSE(PS_.isLoggingIntervallPassed());
}