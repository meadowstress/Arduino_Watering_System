#include<iostream>
#include"mock_arduino.h"
#include<unistd.h>
#include <gtest/gtest.h>

const short PUMP = 8;
const short VALVETOP = 9;
const short VALVEBOTTOM = 10;
const short SWITCH = 7;
const short WATER = 3;
const short WATERLEVEL = 4;

bool switch_on = false;
bool water_on = false;
bool timer_on = false;

TEST(digitalWrite, PUMP_LOW ) 
{ 
    pump_state = false;
    digitalWrite(PUMP,LOW);
    ASSERT_EQ(pump_state, true);
}

TEST(digitalWrite, PUMP_HIGH ) 
{ 
    pump_state = true;
    digitalWrite(PUMP, HIGH);
    ASSERT_EQ(pump_state, false);
}

TEST(digitalWrite, VALVETOP_LOW ) 
{ 
    valve_state_top = false;
    digitalWrite(VALVETOP,LOW);
    ASSERT_EQ(valve_state_top, true);
}

TEST(digitalWrite, VALVETOP_HIGH ) 
{ 
    valve_state_top = true;
    digitalWrite(VALVETOP,HIGH);
    ASSERT_EQ(valve_state_top, false);
}

TEST(digitalWrite, VALVEBOTTOM_LOW ) 
{ 
    valve_state_bottom = false;
    digitalWrite(VALVEBOTTOM,LOW);
    ASSERT_EQ(valve_state_bottom, true);
}

TEST(digitalWrite, VALVEBOTTOM_HIGH ) 
{ 
    valve_state_bottom = true;
    digitalWrite(VALVEBOTTOM,HIGH);
    ASSERT_EQ(valve_state_bottom, false);
}

TEST(digitalRead, PUMP_LOW) 
{ 
    pump_state = true;
    ASSERT_EQ(digitalRead(PUMP), LOW);
}

TEST(digitalRead, PUMP_HIGH) 
{ 
    pump_state = false;
    ASSERT_EQ(digitalRead(PUMP), HIGH);
}

TEST(digitalRead, VALVETOP_LOW) 
{ 
    valve_state_top = true;
    ASSERT_EQ(digitalRead(VALVETOP), LOW);
}

TEST(digitalRead, VALVETOP_HIGH) 
{ 
    valve_state_top = false;
    ASSERT_EQ(digitalRead(VALVETOP), HIGH);
}

TEST(digitalRead, VALVEBOTTOM_LOW) 
{ 
    valve_state_bottom = true;
    ASSERT_EQ(digitalRead(VALVEBOTTOM), LOW);
}

TEST(digitalRead, VALVEBOTTOM_HIGH) 
{ 
    valve_state_bottom = false;
    ASSERT_EQ(digitalRead(VALVEBOTTOM), HIGH);
}

TEST(digitalRead, SWITCH_ON)
{
    switch_state = true;
    ASSERT_EQ(digitalRead(SWITCH), true);
}

TEST(digitalRead, SWITCH_OFF)
{
    switch_state = false;
    ASSERT_EQ(digitalRead(SWITCH), false);
}

TEST(digitalRead, WATER_ON)
{
    water_state = true;
    ASSERT_EQ(digitalRead(WATER), true);
}

TEST(digitalRead, WATER_OFF)
{
    water_state = false;
    ASSERT_EQ(digitalRead(WATER), false);
}

TEST(digitalRead, WATERLEVEL_ON)
{
    water_level_state = true;
    ASSERT_EQ(digitalRead(WATERLEVEL), true);
}

TEST(digitalRead, WATERLEVEL_OFF)
{
    water_level_state = false;
    ASSERT_EQ(digitalRead(WATERLEVEL), false);
}

TEST(Serial, println)
{
    Output Serial;
    Serial.print("String: ");
    Serial.println(" Done!");
    Serial.print(9999L);
    Serial.println(1000L);
    Serial.print(1.375F);
    Serial.print(5.357F);
    Serial.println("");
}

TEST(millis, 10s)
{
    unsigned long start = millis();

    cout <<"Start!\n";
    while((millis()-start) < 3000);
    cout <<"Stop! - 3 s\n";
}
 
int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}