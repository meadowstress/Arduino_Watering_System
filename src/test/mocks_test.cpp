#include <iostream>
#include <string>
#include <unistd.h>
#include <gtest/gtest.h>
#include "time.h"
#include "mock_arduino.h"
#include "PS_func.h"
#include "parameter.h"

TEST(digitalWrite, PUMP_LOW)
{
    pump_state = false;
    digitalWrite(par::PUMP, LOW);
    ASSERT_EQ(pump_state, true);
}

TEST(digitalWrite, PUMP_HIGH)
{
    pump_state = true;
    digitalWrite(par::PUMP, HIGH);
    ASSERT_EQ(pump_state, false);
}

TEST(digitalWrite, VALVETOP_LOW)
{
    valve_state_top = false;
    digitalWrite(par::VALVETOP, LOW);
    ASSERT_EQ(valve_state_top, true);
}

TEST(digitalWrite, VALVETOP_HIGH)
{
    valve_state_top = true;
    digitalWrite(par::VALVETOP, HIGH);
    ASSERT_EQ(valve_state_top, false);
}

TEST(digitalWrite, VALVEBOTTOM_LOW)
{
    valve_state_bottom = false;
    digitalWrite(par::VALVEBOTTOM, LOW);
    ASSERT_EQ(valve_state_bottom, true);
}

TEST(digitalWrite, VALVEBOTTOM_HIGH)
{
    valve_state_bottom = true;
    digitalWrite(par::VALVEBOTTOM, HIGH);
    ASSERT_EQ(valve_state_bottom, false);
}

TEST(digitalRead, PUMP_LOW)
{
    pump_state = true;
    ASSERT_EQ(digitalRead(par::PUMP), LOW);
}

TEST(digitalRead, PUMP_HIGH)
{
    pump_state = false;
    ASSERT_EQ(digitalRead(par::PUMP), HIGH);
}

TEST(digitalRead, VALVETOP_LOW)
{
    valve_state_top = true;
    ASSERT_EQ(digitalRead(par::VALVETOP), LOW);
}

TEST(digitalRead, VALVETOP_HIGH)
{
    valve_state_top = false;
    ASSERT_EQ(digitalRead(par::VALVETOP), HIGH);
}

TEST(digitalRead, VALVEBOTTOM_LOW)
{
    valve_state_bottom = true;
    ASSERT_EQ(digitalRead(par::VALVEBOTTOM), LOW);
}

TEST(digitalRead, VALVEBOTTOM_HIGH)
{
    valve_state_bottom = false;
    ASSERT_EQ(digitalRead(par::VALVEBOTTOM), HIGH);
}

TEST(digitalRead, SWITCH_ON)
{
    switch_state = true;
    ASSERT_EQ(digitalRead(par::SWITCH), LOW);
}

TEST(digitalRead, SWITCH_OFF)
{
    switch_state = false;
    ASSERT_EQ(digitalRead(par::SWITCH), HIGH);
}

TEST(digitalRead, WATER_ON)
{
    water_state = true;
    ASSERT_EQ(digitalRead(par::WATER), LOW);
}

TEST(digitalRead, WATER_OFF)
{
    water_state = false;
    ASSERT_EQ(digitalRead(par::WATER), HIGH);
}

TEST(digitalRead, WATERLEVEL_ON)
{
    water_level_state = true;
    ASSERT_EQ(digitalRead(par::WATERLEVEL), LOW);
}

TEST(digitalRead, WATERLEVEL_OFF)
{
    water_level_state = false;
    ASSERT_EQ(digitalRead(par::WATERLEVEL), HIGH);
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

    cout << "Start!\n";
    while ((millis() - start) < 3000)
        ;
    cout << "Stop! - 3 s\n";
}

TEST(clock, setClock)
{
    DS3231 clock;
    clock.setDateTime(2019, 10, 21, 22, 6, 30);
    ASSERT_EQ(current_local_time.year, 2019);
    ASSERT_EQ(current_local_time.month, 10);
    ASSERT_EQ(current_local_time.day, 21);
    ASSERT_EQ(current_local_time.hour, 22);
    ASSERT_EQ(current_local_time.minute, 6);
    ASSERT_EQ(current_local_time.second, 30);
}

TEST(clock, getLocalTime)
{
    DS3231 clock;
    RTCDateTime time;
    current_local_time.year   = 2019;
    current_local_time.month  = 10;
    current_local_time.day    = 25;
    current_local_time.hour   = 22;
    current_local_time.minute = 5;
    current_local_time.second = 20;

    time = clock.getDateTime();

    ASSERT_EQ(time.year, 2019);
    ASSERT_EQ(time.month, 10);
    ASSERT_EQ(time.day, 25);
    ASSERT_EQ(time.hour, 22);
    ASSERT_EQ(time.minute, 5);
    ASSERT_EQ(time.second, 20);
}