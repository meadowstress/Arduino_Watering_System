#ifndef PS_FUNC_H
#define PS_FUNC_H

#include "DHT.h"     //Enable on Hardware
#include <Wire.h>    //Enable on Hardware
#include <DS3231.h>  //Enable on Hardware

//#include "mock_arduino.h"  //Enable for Testing
#include "mytime.h"

// pins
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

class WaterSystem
{
 public:
    WaterSystem() :
        watering_enabled{false},
        measured_temperature{0.0F},
        sd_card_ok{true},
        pre_state_water{false},
        current_state_water{false},
        switch_on{false},
        water_on{false},
        water_level_ok{false}
    {}
    ~WaterSystem() {}

    int pumpWaterManual();
    int pumpWaterClock();
    int pumpWater(unsigned int pump_time, byte valve_pin, byte valve_time);
    bool holdState(unsigned int hold_time);

    bool checkSystem();
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
    bool isLoggingIntervallPassed();
    bool isSDCardOk();
    String getSDFileName();
    void printToSDFile(const String input);
    void printToSDFile(const int input);
    void printlnToSDFile(const String input);
    void printlnToSDFile(const int input);
    void setPreStateWater(bool input) { pre_state_water = input; }
    void setCurrentStateWater(bool input) { current_state_water = input; }
    void setSwitchState(bool input) { switch_on = input; }
    bool getSwitchState() { return switch_on; }
    void setWaterState(bool input) { water_on = input; }
    void setWaterLevelState(bool input) { water_level_ok = input; }

 private:
    bool watering_enabled;
    float measured_temperature;
    bool sd_card_ok;
    bool pre_state_water;
    bool current_state_water;
    bool switch_on;
    bool water_on;
    bool water_level_ok;
};

// function headers
void printSystemInfo();
void logSDData();
void logSystemInfo();

extern WaterSystem PumpControl;
extern unsigned long global_counter;  // counter for counting cycles

#endif
