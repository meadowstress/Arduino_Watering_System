#include <Wire.h>  // Enable on Hardware

//#include "mock/mock_arduino.h"  //Enable for testing
#include "time.h"
#include "PS_func.h"
#include "parameter.h"
#include <DS3231.h>  //Enable on Hardware

// global states
bool pre_state_water     = false;
bool current_state_water = false;
bool switch_on           = false;
bool water_on            = false;
bool timer_on            = false;
bool water_level_ok      = false;
bool timer_water_flag    = true;

// global states of external devices
DS3231 clock_var;
RTCDateTime DateTime;
DHT dht(par::TEMPERATURE, DHT22);  // Enable for Hardware

// global system variable
WaterSystem PumpControl;

// int main(void)  // Enable for Testing
//{               // Enable for Testing

void setup()  // Enable on Hardware
{

    pinMode(par::PUMP, OUTPUT);         // Enable on Hardware
    pinMode(par::VALVETOP, OUTPUT);     // Enable on Hardware
    pinMode(par::VALVEBOTTOM, OUTPUT);  // Enable on Hardware
    pinMode(par::SWITCH, INPUT);        // Enable on Hardware
    pinMode(par::WATER, INPUT);         // Enable on Hardware
    pinMode(par::WATERLEVEL, INPUT);    // Enable on Hardware
    Serial.begin(9600);                 // Enable on Hardware

    dht.begin();                       // Enable on Hardware
    clock_var.begin();                 // Enable on Hardware
    pinMode(par::CHIPSELECT, OUTPUT);  // Enable on Hardware

    digitalWrite(par::PUMP, HIGH);         // default no pumping enabled
    digitalWrite(par::VALVETOP, HIGH);     // default no pumping enabled
    digitalWrite(par::VALVEBOTTOM, HIGH);  // default no pumping enabled

    // prevent different states when water switch is on
    if (digitalRead(par::WATER) == LOW)
    {
        pre_state_water     = true;
        current_state_water = true;
    }

    Serial.println(F("\n\nStart of Program:"));
    Serial.println("-----------------\n");

}  // Enable on Hardware

unsigned long counter = 0;
TIME t_min(0, 1), t1(0, 0), t2(0, 0), t_buffer(0, 0);

// for (int i = 0; i < 12000; i++)  // enable for Testing
//{                                // enable for Testing

void loop()  // Enable on Hardware
{            // Enable on Hardware

    // configuration settings - change time here
    timer_on = true;  // software switch for pump timer function

    // state logics
    switch_on = PumpControl.isSystemSwitchedOn();
    water_on  = PumpControl.isWaterActivated();

    // log System Info
    counter++;
    if ((counter % 4000) == 0)
    {
        printSystemInfo();

        if (!switch_on)
        {
            logSDData();
        }
    }

    // Manual watering
    // applied only to valve for top plants since there is
    // the manual tube attached for which this feature is designed
    if (switch_on && water_on)
    {
        PumpControl.pumpWater(par::t_half_can, par::VALVETOP, par::t_valve);
    }

    // Watering according to timer
    // timer_water_flag needed since the clock has resolution of 1 min
    // but watering should happen only once during that minute
    if (timer_on &&
        ((PumpControl.getCurrentLocalTime() == par::t1_water) ||
         (PumpControl.getCurrentLocalTime() == par::t2_water)) &&
        timer_water_flag)
    {
        PumpControl.pumpWaterClock();
        timer_water_flag = false;
    }

    // At least log data once a day even without watering
    if ((PumpControl.getCurrentLocalTime() == par::logging_time) ||
        (PumpControl.getCurrentLocalTime() == par::t1_water) ||
        (PumpControl.getCurrentLocalTime() == par::t2_water))
    {
        // timer_water_flag must not be touched that is why an modulo
        // logic is needed until the time resolution of 1 second is
        // implemented
        if ((counter % 2000) == 0)
        {
            logSDData();
        }
    }

    // buffer needed because par::t1::water is const and overloading of
    // + operator is is not defined for const
    t_buffer = par::t1_water;
    t1       = t_buffer + t_min;  // add operator not defined for const times
    t_buffer = par::t2_water;
    t2       = t_buffer + t_min;  // add operator not defined for const times

    // TODO timer_water_flag solution doesn't work when t1 and t2 is
    // only 1 minute apart - apply fix if possible

    // reset timer_water_flag after the minute of watering is past
    if ((PumpControl.getCurrentLocalTime() == t1) ||
        (PumpControl.getCurrentLocalTime() == t2))
    {
        timer_water_flag = true;
    }

    //}  // Enable for Testing
}