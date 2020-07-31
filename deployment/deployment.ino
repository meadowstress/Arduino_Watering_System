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
bool water_level_ok      = false;

// global states of external devices
DS3231 clock_var;
RTCDateTime DateTime;
DHT dht(par::TEMPERATURE, DHT22);  // Enable for Hardware

// global system variable
WaterSystem PumpControl;
unsigned long global_counter = 0;

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
    pinMode(par::MEASURE_WL, OUTPUT);   // Enable on Hardware

    Serial.begin(115200);  // Enable on Hardware

    dht.begin();                       // Enable on Hardware
    clock_var.begin();                 // Enable on Hardware
    pinMode(par::CHIPSELECT, OUTPUT);  // Enable on Hardware

    digitalWrite(par::PUMP, HIGH);         // default no pumping enabled
    digitalWrite(par::VALVETOP, HIGH);     // default no pumping enabled
    digitalWrite(par::VALVEBOTTOM, HIGH);  // default no pumping enabled
    digitalWrite(par::MEASURE_WL, HIGH);   // default no measurement current

    // prevent different states when water switch is on
    if (digitalRead(par::WATER) == LOW)
    {
        pre_state_water     = true;
        current_state_water = true;
    }

    Serial.println(F("\n\nStart of Program:"));
    Serial.println(F("-----------------\n"));

}  // Enable on Hardware

// for (int i = 0; i < 5; i++)  // enable for Testing
//{                            // enable for Testing

void loop()  // Enable on Hardware
{            // Enable on Hardware

    // Check if info should be logged
    logSystemInfo();

    // Check manual watering
    // applied only to valve for top plants since there is
    // the manual tube attached for which this feature is designed
    PumpControl.pumpWaterManual();

    // check automatic watering
    PumpControl.pumpWaterClock();
    //}  // Enable for Testing
}