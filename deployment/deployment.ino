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

// for (int i = 0; i < 5; i++)  // enable for Testing
//{                            // enable for Testing

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
        Serial.println("\nManual Watering is enabled!\n");
        PumpControl.pumpWater(par::t_half_can, par::VALVETOP, par::t_valve);
        PumpControl.printlnToSDFile(F("\nManual Watering is enabled!\n"));
    }

    if (timer_on)
    {
        PumpControl.pumpWaterClock();
    }
    //}  // Enable for Testing
}