#ifndef PS_FUNC_H
#define PS_FUNC_H

#include "DHT.h"    //Enable on Hardware
#include <Wire.h>   //Enable on Hardware
#include <DS3231.h> //Enable on Hardware

//#include "mock_arduino.h" //Enable for Testing
#include "time.h"

//pins
extern const short PUMP;
extern const short VALVETOP;
extern const short VALVEBOTTOM;
extern const short SWITCH;
extern const short WATER;
extern const short WATERLEVEL;
extern const short MEASURE_WL;
extern DHT dht;
extern DS3231 clock_var;
extern RTCDateTime DateTime;

//states
extern bool pre_state_water;
extern bool current_state_water;
extern bool switch_on;
extern bool water_on;
extern bool timer_on;
extern bool water_level_ok;

class WaterSystem
{
private:
    bool watering_enabled;
    float measured_temperature;

public:
    WaterSystem()
    {
        watering_enabled = false;
        measured_temperature = 0.0F;
    }
    ~WaterSystem() {}

    int pumpWaterClock();
    int pumpWater(unsigned long pump_time,
                  unsigned short valve_pin, unsigned long valve_time);
    bool holdState(unsigned long hold_time);

    bool isWaterLevelOk();
    bool isSystemSwitchedOn();
    bool isWaterActivated();
    void updateTemperature();
    unsigned int getWaterTimeTop();
    unsigned int getWaterTimeBottom();
    float getTemperature()
    {
        updateTemperature();
        return (measured_temperature);
    }
    bool getWateringEnabled() { return watering_enabled; }
    bool isAutomaticWateringEnabled();
    TIME getCurrentLocalTime();
};

//function headers
void printCyclicSystemInfo(RTCDateTime DateTime, WaterSystem &PumpControl);

extern WaterSystem PumpControl;

#endif