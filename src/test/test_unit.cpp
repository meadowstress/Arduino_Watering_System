#include <gtest/gtest.h>
#include "../time.h"
#include "../mock/mock_arduino.h"
#include "../PS_func.h"
#include "../parameter.h"

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

class TimeTest : public ::testing::Test
{
protected:
    TimeTest()
    {
        // initialization code here
    }

    void SetUp()
    {
        // code here will execute just before the test ensues
        t = new TIME(1, 0);
    }

    void TearDown()
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
        delete (t);
    }

    ~TimeTest()
    {
        // cleanup any pending stuff, but no exceptions allowed
    }

    // put in any custom data members that you need
    TIME *t;
};

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

TEST_F(TimeTest, Time2TicksTest)
{
    ASSERT_EQ(t->Time2Ticks(), 3600000);
}

TEST(Time, Time2Ticks)
{
    TIME t(0, 1);
    ASSERT_EQ(t.Time2Ticks(), 60000);
}

TEST(Time, operator_GT)
{
    TIME t1(15, 30), t2(14, 45);
    ASSERT_TRUE(t1 > t2);
    ASSERT_FALSE(t2 > t1);
}

TEST(Time, operator_GTE)
{
    TIME t1(15, 30), t2(14, 45), t3(15, 30);
    ASSERT_TRUE(t1 >= t2);
    ASSERT_FALSE(t2 >= t1);
    ASSERT_TRUE(t1 >= t3);
    ASSERT_TRUE(t3 >= t1);
}

TEST(Time, operator_LT)
{
    TIME t2(15, 30), t1(14, 45);
    ASSERT_TRUE(t1 < t2);
    ASSERT_FALSE(t2 < t1);
}

TEST(Time, operator_LTE)
{
    TIME t2(15, 30), t1(14, 45), t3(15, 30);
    ASSERT_TRUE(t1 <= t2);
    ASSERT_FALSE(t2 <= t1);
    ASSERT_TRUE(t2 <= t3);
    ASSERT_TRUE(t3 <= t2);
}

TEST(Time, operator_EQ)
{
    TIME t1(15, 30), t2(15, 30);
    ASSERT_TRUE(t1 == t2);
}

TEST(Time, operator_plus)
{
    TIME t1(14, 45), t2(15, 30), t3(6, 15);
    ASSERT_TRUE((t1 + t2) == t3);
    t1.set_Time(5, 0);
    t2.set_Time(6, 30);
    t3.set_Time(11, 30);
    ASSERT_TRUE((t1 + t2) == t3);
}

TEST(Time, operator_minus)
{
    TIME t2(14, 45), t1(15, 30), t3(0, 45);
    ASSERT_TRUE((t1 - t2) == t3);
    t2.set_Time(5, 0);
    t1.set_Time(6, 30);
    t3.set_Time(1, 30);
    ASSERT_TRUE((t1 - t2) == t3);
}

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

TEST_F(WaterSystemTest, PS_func_isWaterActivatedTrueFF)
{
    pre_state_water = false;
    current_state_water = false;

    water_state = true;
    ASSERT_TRUE(PS_.isWaterActivated());
}

TEST_F(WaterSystemTest, PS_func_isWaterActivatedFalseFF)
{
    pre_state_water = false;
    current_state_water = false;

    water_state = false;
    ASSERT_FALSE(PS_.isWaterActivated());
}

TEST(PS_func, isWaterActivatedTrueTT)
{
    WaterSystem PS;

    pre_state_water = true;
    current_state_water = true;

    water_state = false;
    ASSERT_TRUE(PS.isWaterActivated());
}

TEST(PS_func, isWaterActivatedFalseTT)
{
    WaterSystem PS;

    pre_state_water = true;
    current_state_water = true;

    water_state = true;
    ASSERT_FALSE(PS.isWaterActivated());
}

TEST(holdState, SwitchOn)
{
    WaterSystem PS;
    switch_state = true;
    water_level_state = true;
    measure_current_wl = true;
    ASSERT_TRUE(PS.holdState(3000));
}

TEST(holdState, SwitchOff)
{
    WaterSystem PS;
    switch_state = false;
    water_level_state = true;
    measure_current_wl = true;
    ASSERT_FALSE(PS.holdState(3000));
}

//Deactivation of water level feature
/* 
TEST(holdState, LowLevel)
{
    WaterSystem PS;
    switch_state = true;
    water_level_state = false;
    measure_current_wl = true;
    ASSERT_FALSE(PS.holdState(3000));
}
*/

TEST(pumpWater, SwitchOn)
{
    WaterSystem PS;
    unsigned long pump_time = par::t_half_can;
    unsigned short valve_pin = VALVETOP;
    unsigned long valve_time = par::t_valve;

    water_level_state = true;
    switch_state = true;

    ASSERT_EQ(PS.pumpWater(pump_time, valve_pin, valve_time), 1);
}

TEST(pumpWater, SwitchOff)
{
    WaterSystem PS;
    unsigned long pump_time = par::t_half_can;
    unsigned short valve_pin = VALVETOP;
    unsigned long valve_time = par::t_valve;
    int result = 0;

    water_level_state = true;
    switch_state = false;

    result = PS.pumpWater(pump_time, valve_pin, valve_time);
    ASSERT_EQ(result, 0);
}

//Deactivation of water level feature
/*
TEST(pumpWater,LowLevel)
{
    WaterSystem PS;
    unsigned long pump_time = t_half_can; 
    unsigned short valve_pin = VALVETOP; 
    unsigned long valve_time = t_valve;
    int result = 0;

    water_level_state = false;
    switch_state = true;

    result = PS.pumpWater(pump_time, valve_pin, valve_time);
    ASSERT_EQ(result, 0);
}

TEST(pumpWater,SwitchOffLowLevel)
{
    WaterSystem PS;
    unsigned long pump_time = t_half_can; 
    unsigned short valve_pin = VALVETOP; 
    unsigned long valve_time = t_valve;
    int result = 0;

    water_level_state = false;
    switch_state = false;

    result = PS.pumpWater(pump_time, valve_pin, valve_time);
    ASSERT_EQ(result, 0);
}
*/

TEST(Temperature, timeMaxTempTop)
{
    WaterSystem PS;
    unsigned int time = 0;

    temperature_value = par::maxTemp;
    time = PS.getWaterTimeTop();

    ASSERT_FLOAT_EQ(time, par::timeMaxTempTop);

    temperature_value = par::maxTemp + 1.0F;
    time = PS.getWaterTimeTop();

    ASSERT_EQ(time, par::timeMaxTempTop);
}

TEST(Temperature, timeTemp2Top)
{
    WaterSystem PS;
    unsigned int time = 0;

    temperature_value = par::temp2;
    time = PS.getWaterTimeTop();

    ASSERT_EQ(time, par::timeTemp2Top);

    temperature_value = par::temp2 + 1.0F;
    time = PS.getWaterTimeTop();

    ASSERT_EQ(time, par::timeTemp2Top);
}

TEST(Temperature, timeTemp3Top)
{
    WaterSystem PS;
    unsigned int time = 0;

    temperature_value = par::temp3;
    time = PS.getWaterTimeTop();

    ASSERT_EQ(time, par::timeTemp3Top);

    temperature_value = par::temp3 + 1.0F;
    time = PS.getWaterTimeTop();

    ASSERT_EQ(time, par::timeTemp3Top);
}

TEST(Temperature, timeTemp4Top)
{
    WaterSystem PS;
    unsigned int time = 0;

    temperature_value = par::temp4;
    time = PS.getWaterTimeTop();

    ASSERT_EQ(time, par::timeTemp4Top);

    temperature_value = par::temp4 + 1.0F;
    time = PS.getWaterTimeTop();

    ASSERT_EQ(time, par::timeTemp4Top);
}

TEST(Temperature, timeLowTempTop)
{
    WaterSystem PS;
    unsigned int time = 0;

    temperature_value = par::lowTemp;
    time = PS.getWaterTimeTop();

    ASSERT_EQ(time, par::timeLowTempTop);

    temperature_value = par::lowTemp + 1.0F;
    time = PS.getWaterTimeTop();

    ASSERT_EQ(time, par::timeLowTempTop);
}

TEST(Temperature, belowLowTempTop)
{
    WaterSystem PS;
    unsigned int time = 0;

    temperature_value = par::lowTemp - 1.0F;
    time = PS.getWaterTimeTop();

    ASSERT_EQ(time, 0);

    temperature_value = 0.0F;
    time = PS.getWaterTimeTop();

    ASSERT_EQ(time, 0);
}

TEST(Temperature, timeMaxTempBottom)
{
    WaterSystem PS;
    unsigned int time = 0;

    temperature_value = par::maxTemp;
    time = PS.getWaterTimeBottom();

    ASSERT_FLOAT_EQ(time, par::timeMaxTempBottom);

    temperature_value = par::maxTemp + 1.0F;
    time = PS.getWaterTimeBottom();

    ASSERT_EQ(time, par::timeMaxTempBottom);
}

TEST(Temperature, timeTemp2Bottom)
{
    WaterSystem PS;
    unsigned int time = 0;

    temperature_value = par::temp2;
    time = PS.getWaterTimeBottom();

    ASSERT_EQ(time, par::timeTemp2Bottom);

    temperature_value = par::temp2 + 1.0F;
    time = PS.getWaterTimeBottom();

    ASSERT_EQ(time, par::timeTemp2Bottom);
}

TEST(Temperature, timeTemp3Bottom)
{
    WaterSystem PS;
    unsigned int time = 0;

    temperature_value = par::temp3;
    time = PS.getWaterTimeBottom();

    ASSERT_EQ(time, par::timeTemp3Bottom);

    temperature_value = par::temp3 + 1.0F;
    time = PS.getWaterTimeBottom();

    ASSERT_EQ(time, par::timeTemp3Bottom);
}

TEST(Temperature, timeTemp4Bottom)
{
    WaterSystem PS;
    unsigned int time = 0;

    temperature_value = par::temp4;
    time = PS.getWaterTimeBottom();

    ASSERT_EQ(time, par::timeTemp4Bottom);

    temperature_value = par::temp4 + 1.0F;
    time = PS.getWaterTimeBottom();

    ASSERT_EQ(time, par::timeTemp4Bottom);
}

TEST(Temperature, lowTempBottom)
{
    WaterSystem PS;
    unsigned int time = 0;

    temperature_value = par::lowTemp;
    time = PS.getWaterTimeBottom();

    ASSERT_EQ(time, par::timeLowTempBottom);

    temperature_value = par::lowTemp + 1.0F;
    time = PS.getWaterTimeBottom();

    ASSERT_EQ(time, par::timeLowTempBottom);
}

TEST(Temperature, belowLowTempBottom)
{
    WaterSystem PS;
    unsigned int time = 0;

    temperature_value = par::lowTemp - 1.0F;
    time = PS.getWaterTimeBottom();

    ASSERT_EQ(time, 0);

    temperature_value = 0.0F;
    time = PS.getWaterTimeBottom();

    ASSERT_EQ(time, 0);
}

TEST(WateringEnabled, true)
{
    WaterSystem PS;

    temperature_value = 18.0F;
    ASSERT_TRUE(PS.isAutomaticWateringEnabled());
    temperature_value = 20.0F;
    ASSERT_TRUE(PS.isAutomaticWateringEnabled());
}

TEST(isWateringEnabled, false)
{
    WaterSystem PS;

    temperature_value = 0.0F;
    ASSERT_FALSE(PS.isAutomaticWateringEnabled());
    temperature_value = 5.0F;
    ASSERT_FALSE(PS.isAutomaticWateringEnabled());
}

TEST(Pump_Water_Clock, watering_true_t1)
{
    WaterSystem PS;

    temperature_value = 20.0F;
    switch_state = true;

    current_local_time.hour = 11;
    current_local_time.minute = 30;
    ASSERT_EQ(PS.pumpWaterClock(), 2);
}

TEST(Pump_Water_Clock, watering_true_t2)
{
    WaterSystem PS;

    temperature_value = 20.0F;
    switch_state = true;

    current_local_time.hour = 15;
    current_local_time.minute = 30;
    ASSERT_EQ(PS.pumpWaterClock(), 2);
}

TEST(Pump_Water_Clock, watering_false_t1)
{
    WaterSystem PS;

    temperature_value = 20.0F;
    switch_state = true;

    current_local_time.hour = 10;
    current_local_time.minute = 30;
    ASSERT_EQ(PS.pumpWaterClock(), 0);

    current_local_time.hour = 12;
    current_local_time.minute = 30;
    ASSERT_EQ(PS.pumpWaterClock(), 0);

    current_local_time.hour = 14;
    current_local_time.minute = 30;
    ASSERT_EQ(PS.pumpWaterClock(), 0);

    current_local_time.hour = 16;
    current_local_time.minute = 30;
    ASSERT_EQ(PS.pumpWaterClock(), 0);

    current_local_time.hour = 0;
    current_local_time.minute = 0;
    ASSERT_EQ(PS.pumpWaterClock(), 0);
}

TEST(Pump_Water_Clock, switch_off)
{
    WaterSystem PS;

    temperature_value = 20.0F;
    switch_state = false;

    current_local_time.hour = 11;
    current_local_time.minute = 30;
    ASSERT_EQ(PS.pumpWaterClock(), 0);
}

TEST(Pump_Water_Clock, low_temperature)
{
    WaterSystem PS;

    temperature_value = 16.0F;
    switch_state = true;

    current_local_time.hour = 11;
    current_local_time.minute = 30;
    ASSERT_EQ(PS.pumpWaterClock(), 0);
}

TEST(systemTime, getLocalTime)
{
    WaterSystem PS;
    TIME t(0, 0);

    temperature_value = 20.0F;
    switch_state = true;

    current_local_time.hour = 15;
    current_local_time.minute = 13;

    t = PS.getCurrentLocalTime();
    ASSERT_EQ(t.get_H(), 15);
    ASSERT_EQ(t.get_Min(), 13);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}