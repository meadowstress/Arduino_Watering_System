#include <gtest/gtest.h>
#include "time.h"
#include "mock_arduino.h"
#include "PS_func.h"

const short PUMP = 8;
const short VALVETOP = 9;
const short VALVEBOTTOM = 10;
const short SWITCH = 7;
const short WATER = 3;
const short WATERLEVEL = 4;

bool pre_state_water = false;
bool current_state_water = false;
bool switch_on = false;
bool water_on = false;
bool timer_on = false;
bool water_level_ok = false;

unsigned long const t_half_can = 15000;
unsigned long const t_half_vol = 40000;
unsigned long const t_quater_vol = 20000;
unsigned long const t_valve = 100;
unsigned long const t_bottom_vol = 6000;

class TimeTest: public ::testing::Test 
{ 
    protected: 

        TimeTest( ) 
        { 
            // initialization code here
        } 

        void SetUp( ) 
        { 
            // code here will execute just before the test ensues 
            t = new TIME(1,0);
        }

        void TearDown( ) 
        { 
            // code here will be called just after the test completes
            // ok to through exceptions from here if need be
            delete(t);
        }
         

        ~TimeTest( )
        { 
            // cleanup any pending stuff, but no exceptions allowed
        }

        // put in any custom data members that you need
        TIME* t;
};


TEST_F(TimeTest, Time2TicksTest)
{
    ASSERT_EQ(t->Time2Ticks(), 3600000);
}

TEST(Time, Time2Ticks)
{
    TIME t(0,1);
    ASSERT_EQ(t.Time2Ticks(), 60000);
}

TEST(Time, operator_GT)
{
    TIME t1(15,30), t2(14,45);
    ASSERT_TRUE(t1>t2);
    ASSERT_FALSE(t2>t1);
}

TEST(Time, operator_GTE)
{
    TIME t1(15,30), t2(14,45), t3(15,30);
    ASSERT_TRUE(t1>=t2);
    ASSERT_FALSE(t2>=t1);
    ASSERT_TRUE(t1>=t3);
    ASSERT_TRUE(t3>=t1);
}

TEST(Time, operator_LT)
{
    TIME t2(15,30), t1(14,45);
    ASSERT_TRUE(t1<t2);
    ASSERT_FALSE(t2<t1);
}

TEST(Time, operator_LTE)
{
    TIME t2(15,30), t1(14,45), t3(15,30);
    ASSERT_TRUE(t1<=t2);
    ASSERT_FALSE(t2<=t1);
    ASSERT_TRUE(t2<=t3);
    ASSERT_TRUE(t3<=t2);
}

TEST(Time, operator_EQ)
{
    TIME t1(15,30), t2(15,30);
    ASSERT_TRUE(t1==t2);
}

TEST(Time, operator_plus)
{
    TIME t1(14,45), t2(15,30), t3(6,15);
    ASSERT_TRUE((t1+t2)==t3);
    t1.set_Time(5,0); t2.set_Time(6,30); t3.set_Time(11,30);
    ASSERT_TRUE((t1+t2)==t3);
}

TEST(Time, operator_minus)
{
    TIME t2(14,45), t1(15,30), t3(0,45);
    ASSERT_TRUE((t1-t2)==t3);
    t2.set_Time(5,0); t1.set_Time(6,30); t3.set_Time(1,30);
    ASSERT_TRUE((t1-t2)==t3);
}


TEST(PS_func, State_Switch) 
{ 
    ASSERT_TRUE( State_Switch(LOW));
    ASSERT_FALSE( State_Switch(HIGH));
}

TEST(PS_func, State_Water_ff)
{
    water_on = false;
    pre_state_water = false;
    current_state_water = false;

    water_state = false;
    State_Water();
    water_state = false;
    State_Water();
    ASSERT_EQ(water_on, false);
}

TEST(PS_func, State_Water_tt)
{
    water_on = false;
    pre_state_water = true;
    current_state_water = true;

    water_state = true;
    State_Water();
    water_state = true;
    State_Water();
    ASSERT_EQ(water_on, false);
}

TEST(PS_func, State_Water_ft)
{
    water_on = false;
    pre_state_water = false;
    current_state_water = false;

    water_state = false;
    State_Water();
    water_state = true;
    State_Water();
    ASSERT_EQ(water_on, true);
}

TEST(PS_func, State_Water_tf)
{
    water_on = false;
    pre_state_water = true;
    current_state_water = true;

    water_state = true;
    State_Water();
    water_state = false;
    State_Water();
    ASSERT_EQ(water_on, true);
}
 
TEST(PS_func, Hold_State)
{
    switch_state = true;
    Hold_State(3000);
}

TEST(PS_func, Pump_Water)
{
    unsigned long pump_time = t_half_can; 
    unsigned short valve_pin = VALVETOP; 
    unsigned long valve_time = t_valve;
    ASSERT_EQ(Pump_Water(pump_time, valve_pin, valve_time), 1);
}

TEST(PS_func, Hold_State_Clock)
{
    unsigned long hold_time = 60000;
    TIME t(0,1);
    unsigned long pump_time = 3000;
    Hold_State_Clock(hold_time, t, pump_time);
}

TEST(Pump_Water_Clock, Before_Water_Counter)
{
    int water_counter = 0;
    unsigned long pump_time_top = 3000;
    unsigned long pump_time_bottom = 3000;
    water_level_state = true;
    switch_state = true;
    
    TIME t_curr(8,0), t1_water(10,0), t2_water(15,0);
    
    water_counter = Pump_Water_Clock(pump_time_top, pump_time_bottom,
    t_curr, t1_water, t2_water);

    ASSERT_EQ(water_counter, 8);
}

TEST(Pump_Water_Clock, Between_Water_Counter)
{
    int water_counter = 0;
    unsigned long pump_time_top = 3000;
    unsigned long pump_time_bottom = 3000;
    water_level_state = true;
    switch_state = true;
    
    TIME t_curr(12,0), t1_water(10,0), t2_water(15,0);
    
    water_counter = Pump_Water_Clock(pump_time_top, pump_time_bottom,
    t_curr, t1_water, t2_water);

    ASSERT_EQ(water_counter, 10);
}

TEST(Pump_Water_Clock, After_Water_Counter)
{
    int water_counter = 0;
    unsigned long pump_time_top = 3000;
    unsigned long pump_time_bottom = 3000;
    water_level_state = true;
    switch_state = true;
    
    TIME t_curr(18,0), t1_water(10,0), t2_water(15,0);
    
    water_counter = Pump_Water_Clock(pump_time_top, pump_time_bottom,
    t_curr, t1_water, t2_water);

    ASSERT_EQ(water_counter, 8);
}

TEST(Pump_Water_Clock, Before_pre_pause1)
{
    int water_counter = 0;
    unsigned long pump_time_top = 3000;
    unsigned long pump_time_bottom = 3000;

    water_level_state = true;
    switch_state = true;
    
    TIME t_curr(8,0), t1_water(10,0), t2_water(15,0);
    
    water_counter = Pump_Water_Clock(pump_time_top, pump_time_bottom,
    t_curr, t1_water, t2_water);

    unsigned long p = 2*3600*1000;
    unsigned long t = pre_pause1.Time2Ticks();

    ASSERT_EQ(t, p);
}

TEST(Pump_Water_Clock, Between_pre_pause1)
{
    int water_counter = 0;
    unsigned long pump_time_top = 3000;
    unsigned long pump_time_bottom = 3000;
    
    water_level_state = true;
    switch_state = true;

    TIME t_curr(12,0), t1_water(10,0), t2_water(15,0);
    
    water_counter = Pump_Water_Clock(pump_time_top, pump_time_bottom,
    t_curr, t1_water, t2_water);

    unsigned long p = 3*3600*1000;
    unsigned long t = pre_pause1.Time2Ticks();

    ASSERT_EQ(t, p);
}

TEST(Pump_Water_Clock, After_pre_pause1)
{
    int water_counter = 0;
    unsigned long pump_time_top = 3000;
    unsigned long pump_time_bottom = 3000;
    
    water_level_state = true;
    switch_state = true;

    TIME t_curr(18,0), t1_water(10,0), t2_water(15,0);
    
    water_counter = Pump_Water_Clock(pump_time_top, pump_time_bottom,
    t_curr, t1_water, t2_water);

    unsigned long p = 16*3600*1000;
    unsigned long t = pre_pause1.Time2Ticks();

    ASSERT_EQ(t, p);
}

TEST(Pump_Water_Clock, Between_pre_pause2)
{
    int water_counter = 0;
    unsigned long pump_time_top = 3000;
    unsigned long pump_time_bottom = 3000;

    water_level_state = true;
    switch_state = true;
    
    TIME t_curr(12,0), t1_water(10,0), t2_water(15,0);
    
    water_counter = Pump_Water_Clock(pump_time_top, pump_time_bottom,
    t_curr, t1_water, t2_water);
    
    unsigned long p = 19*3600*1000;
    unsigned long t = pre_pause2.Time2Ticks();
    ASSERT_EQ(t, p);
}

TEST(Pump_Water_Clock, Before_pause1_water)
{
    int water_counter = 0;
    unsigned long pump_time_top = 3000;
    unsigned long pump_time_bottom = 3000;

    water_level_state = true;
    switch_state = true;
    
    TIME t_curr(8,0), t1_water(10,0), t2_water(15,0);
    
    water_counter = Pump_Water_Clock(pump_time_top, pump_time_bottom,
    t_curr, t1_water, t2_water);

    unsigned long p = 5 * 3600 * 1000;
    unsigned long t = pause1_water.Time2Ticks();

    ASSERT_EQ(t, p);
}

TEST(Pump_Water_Clock, Between_pause1_water)
{
    int water_counter = 0;
    unsigned long pump_time_top = 3000;
    unsigned long pump_time_bottom = 3000;

    water_level_state = true;
    switch_state = true;
    
    TIME t_curr(12,0), t1_water(10,0), t2_water(15,0);
    
    water_counter = Pump_Water_Clock(pump_time_top, pump_time_bottom,
    t_curr, t1_water, t2_water);

    unsigned long p = 5 * 3600 * 1000;
    unsigned long t = pause1_water.Time2Ticks();

    ASSERT_EQ(t, p);
}

TEST(Pump_Water_Clock, After_pause1_water)
{
    int water_counter = 0;
    unsigned long pump_time_top = 3000;
    unsigned long pump_time_bottom = 3000;

    water_level_state = true;
    switch_state = true;
    
    TIME t_curr(18,0), t1_water(10,0), t2_water(15,0);
    
    water_counter = Pump_Water_Clock(pump_time_top, pump_time_bottom,
    t_curr, t1_water, t2_water);

    unsigned long p = 5 * 3600 * 1000;
    unsigned long t = pause1_water.Time2Ticks();

    ASSERT_EQ(t, p);
}

TEST(Pump_Water_Clock, Before_pause2_water)
{
    int water_counter = 0;
    unsigned long pump_time_top = 3000;
    unsigned long pump_time_bottom = 3000;

    water_level_state = true;
    switch_state = true;
    
    TIME t_curr(8,0), t1_water(10,0), t2_water(15,0);
    
    water_counter = Pump_Water_Clock(pump_time_top, pump_time_bottom,
    t_curr, t1_water, t2_water);

    long p = 19*3600*1000;
    long t = pause2_water.Time2Ticks();
    ASSERT_EQ(t,p);
}

TEST(Pump_Water_Clock, Between_pause2_water)
{
    int water_counter = 0;
    unsigned long pump_time_top = 3000;
    unsigned long pump_time_bottom = 3000;

    water_level_state = true;
    switch_state = true;
    
    TIME t_curr(12,0), t1_water(10,0), t2_water(15,0);
    
    water_counter = Pump_Water_Clock(pump_time_top, pump_time_bottom,
    t_curr, t1_water, t2_water);

    long p = 19*3600*1000;
    long t = pause2_water.Time2Ticks();
    ASSERT_EQ(t,p);
}

TEST(Pump_Water_Clock, After_pause2_water)
{
    int water_counter = 0;
    unsigned long pump_time_top = 3000;
    unsigned long pump_time_bottom = 3000;

    water_level_state = true;
    switch_state = true;
    
    TIME t_curr(18,0), t1_water(10,0), t2_water(15,0);
    
    water_counter = Pump_Water_Clock(pump_time_top, pump_time_bottom,
    t_curr, t1_water, t2_water);

    long p = 19*3600*1000;
    long t = pause2_water.Time2Ticks();
    ASSERT_EQ(t,p);
}

int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}