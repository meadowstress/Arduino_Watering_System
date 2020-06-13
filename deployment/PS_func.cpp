#include "PS_func.h"
//#include "mock/mock_arduino.h"  //Enable for Testing
#include "parameter.h"
#include <string.h>

#include <Arduino.h>         //Enable on Hardware
#include <HardwareSerial.h>  //Enable on Hardware
#include "DHT.h"             //Enable on Hardware
#include <Wire.h>            //Enable on Hardware
#include <DS3231.h>          //Enable on Hardware
#include <SPI.h>
#include <SD.h>


bool WaterSystem::isSDCardOk()
{
    bool isSDCardOk = SD.begin(par::CHIPSELECT);
    return (isSDCardOk);
}

String WaterSystem::getSDFileName()
{
    // using global time variable for date
    String year  = String(DateTime.year);
    String month = String(DateTime.month);
    String day   = String(DateTime.day);

    String fname = year + month + day;
    return (fname);
}

void WaterSystem::printToSDFile(const String input)
{
    File logFile;
    String fname = getSDFileName();

    if (isSDCardOk())
    {
        logFile = SD.open(fname, FILE_WRITE);
        logFile.print(input);
        logFile.close();
    }
    else
    {
        Serial.println("\nWriting to SD Card not successful!\n");
    }
}

void WaterSystem::printToSDFile(const byte input)
{
    File logFile;
    String fname = getSDFileName();

    if (isSDCardOk())
    {
        logFile = SD.open(fname, FILE_WRITE);
        logFile.print(input);
        logFile.close();
    }
    else
    {
        Serial.println("\nWriting to SD Card not successful!\n");
    }
}

// support function
void printCyclicSystemInfo(const WaterSystem &PumpControl)
{
    TIME t1(0, 0), t2(0, 0);
    unsigned int ms = 0;

    Serial.print(DateTime.day);
    Serial.print(F("."));
    Serial.print(DateTime.month);
    Serial.print(F("."));
    Serial.print(DateTime.year);
    Serial.print(F(": "));
    Serial.print(DateTime.hour);
    Serial.print(F(":"));
    Serial.print(DateTime.minute);
    Serial.print(F("   "));

    PumpControl.printToSDFile(DateTime.day);
    PumpControl.printToSDFile(F("."));
    PumpControl.printToSDFile(DateTime.month);
    PumpControl.printToSDFile(F("."));
    PumpControl.printToSDFile(DateTime.year);
    PumpControl.printToSDFile(F(": "));
    PumpControl.printToSDFile(DateTime.hour);
    PumpControl.printToSDFile(F(":"));
    PumpControl.printToSDFile(DateTime.minute);
    PumpControl.printToSDFile(F("   "));

    // Temperature
    Serial.print(F("Temperature = "));
    Serial.print(PumpControl.getTemperature());
    Serial.print(F(" Celsius\n"));

    PumpControl.printToSDFile(F("Temperature = "));
    PumpControl.printToSDFile(PumpControl.getTemperature());
    PumpControl.printToSDFile(F(" Celsius\n"));

    // Watering Parameters
    Serial.print(F("Watering Parameters: "));
    Serial.print(F("t1_water = "));
    t1 = par::t1_water;
    t1.print();  // print function not defined for const times
    Serial.print(F("; "));
    Serial.print(F("t2_water = "));
    t2 = par::t2_water;
    t2.println();  // print function not defined for const times

    // Currently selected Temperature Range
    ms = PumpControl.getWaterTimeTop();
    Serial.print(F("Current chosen ms for top watering: "));
    Serial.println(ms);
    ms = PumpControl.getWaterTimeBottom();
    Serial.print(F("Current chosen ms for bottom watering: "));
    Serial.println(ms);

    // distance to next cyclic message
    Serial.println(F(""));
}

// Hold logic
bool WaterSystem::holdState(unsigned int hold_time)
{

    bool state_flag            = true;
    unsigned long start_time   = millis();
    unsigned long elapsed_time = 0;
    int i                      = 0;

    do
    {
        i++;
        switch_on      = isSystemSwitchedOn();
        water_level_ok = isWaterLevelOk();  // has to be evaluated if test test
                                            // for waterlevel is applicable

        elapsed_time = (millis() - start_time);
        if ((elapsed_time > hold_time) || switch_on == false ||
            water_level_ok == false)
        {
            state_flag = false;
        }
    } while (state_flag);

    // test if hold time has been elapsed regularly
    // var i is only necessary for time simulation with high factors
    if ((elapsed_time > hold_time) && i > 1)
        return true;
    else
        return false;
}

int WaterSystem::pumpWater(unsigned int pump_time,
                           byte valve_pin,
                           byte valve_time)
{
    bool water_flag = false;

    switch_on      = isSystemSwitchedOn();
    water_level_ok = isWaterLevelOk();

    if (switch_on && water_level_ok)
    {
        Serial.println(F("Open Valve!"));
        digitalWrite(valve_pin, LOW);
        holdState(valve_time);

        Serial.println(F("Pump Water!"));
        digitalWrite(par::PUMP, LOW);  // pumping starts
        water_flag = holdState(pump_time);
        digitalWrite(par::PUMP, HIGH);  // pumping ends

        holdState(valve_time);
        digitalWrite(valve_pin, HIGH);  // closing Valve
        water_on = false;               // state for interupt!
        Serial.println(F(""));
    }

    if (water_flag == true)
        return (1);
    else
        return (0);
}

int WaterSystem::pumpWaterClock()
{
    int water_counter = 0;

    if (getCurrentLocalTime() == par::t1_water ||
        getCurrentLocalTime() == par::t2_water)
    {
        switch_on      = isSystemSwitchedOn();
        water_level_ok = isWaterLevelOk();

        if (switch_on && water_level_ok && isAutomaticWateringEnabled())
        {
            DateTime = clock_var.getDateTime();
            Serial.println(F(""));
            Serial.print(DateTime.day);
            Serial.print(F("."));
            Serial.print(DateTime.month);
            Serial.print(F("."));
            Serial.print(DateTime.year);
            Serial.print(F(": "));
            Serial.print(DateTime.hour);
            Serial.print(F(":"));
            Serial.print(DateTime.minute);
            Serial.print(F("   "));
            Serial.print(F("Temperature = "));
            Serial.print(getTemperature());
            Serial.println(F(" Celsius"));
            Serial.print(F("WaterTimeTop = "));
            Serial.print(getWaterTimeTop());
            Serial.println(F(" ms"));
            Serial.print(F("WaterTimeBottom = "));
            Serial.print(getWaterTimeBottom());
            Serial.println(F(" ms"));
            Serial.println(F(""));

            water_counter +=
                pumpWater(getWaterTimeTop(), par::VALVETOP, par::t_valve);
            water_counter +=
                pumpWater(getWaterTimeBottom(), par::VALVEBOTTOM, par::t_valve);
        }
    }

    return (water_counter);
}

bool WaterSystem::isWaterLevelOk()
{
    // Deactivation of water level feature
    /*
      int level_Ok = false;
      digitalWrite(par::MEASURE_WL, LOW); //measurement current switched on
      level_Ok = digitalRead(WATERLEVEL);
      digitalWrite(par::MEASURE_WL, HIGH); //measurement current switched off

      if(level_Ok == LOW)
      {
        return true;
      }
      else
      {
        return false;
      }
      */
    return true;
}

bool WaterSystem::isSystemSwitchedOn()
{
    bool state = false;
    state      = (bool)digitalRead(par::SWITCH);
    if (state == LOW)
        return true;
    else
        return false;
}

bool WaterSystem::isWaterActivated()
{
    if (digitalRead(par::WATER) == LOW)
    {
        current_state_water = true;
    }
    else
    {
        current_state_water = false;
    }

    if (current_state_water != pre_state_water)
    {
        pre_state_water = current_state_water;
        return true;
    }
    else
        return false;
}

void WaterSystem::updateTemperature()
{
    measured_temperature = dht.readTemperature();
}

bool WaterSystem::isAutomaticWateringEnabled()
{
    updateTemperature();

    if (getTemperature() >= 18.0F)
        watering_enabled = true;
    else
        watering_enabled = false;

    return (watering_enabled);
}

unsigned int WaterSystem::getWaterTimeTop()
{
    float temperature = 0.0F;
    int water_time_ms = 0;

    updateTemperature();
    temperature = getTemperature();

    if (temperature >= par::maxTemp)
    {
        water_time_ms = par::timeMaxTempTop;
        Serial.println(F("Chosen Time Constant = par::timeMaxTempTop"));
    }
    else if (temperature >= par::temp4)
    {
        water_time_ms = par::timeTemp4Top;
        Serial.println(F("Chosen Time Constant = par::timeTemp4Top"));
    }
    else if (temperature >= par::temp3)
    {
        water_time_ms = par::timeTemp3Top;
        Serial.println(F("Chosen Time Constant = par::timeTemp3Top"));
    }
    else if (temperature >= par::temp2)
    {
        water_time_ms = par::timeTemp2Top;
        Serial.println(F("Chosen Time Constant = par::timeTemp2Top"));
    }
    else if (temperature >= par::lowTemp)
    {
        water_time_ms = par::timeLowTempTop;
        Serial.println(F("Chosen Time Constant = par::lowTemp"));
    }
    else
    {
        water_time_ms = 0;
        Serial.println(F("No Watering Temperature too low!"));
    }
    return water_time_ms;
}

unsigned int WaterSystem::getWaterTimeBottom()
{
    float temperature = 0.0F;
    int water_time_ms = 0;

    updateTemperature();
    temperature = getTemperature();

    if (temperature >= par::maxTemp)
    {
        water_time_ms = par::timeMaxTempBottom;
        Serial.println(F("Chosen Time Constant = par::timeMaxTempBottom"));
    }
    else if (temperature >= par::temp4)
    {
        water_time_ms = par::timeTemp4Bottom;
        Serial.println(F("Chosen Time Constant = par::timeTemp4Bottom"));
    }
    else if (temperature >= par::temp3)
    {
        water_time_ms = par::timeTemp3Bottom;
        Serial.println(F("Chosen Time Constant = par::timeTemp3Bottom"));
    }
    else if (temperature >= par::temp2)
    {
        water_time_ms = par::timeTemp2Bottom;
        Serial.println(F("Chosen Time Constant = par::timeTemp2Bottom"));
    }
    else if (temperature >= par::lowTemp)
    {
        water_time_ms = par::timeLowTempBottom;
        Serial.println(F("Chosen Time Constant = par::timeLowTempBottom"));
    }
    else
    {
        water_time_ms = 0;
        Serial.println(F("No Watering Temperature too low!"));
    }
    return water_time_ms;
}

TIME WaterSystem::getCurrentLocalTime()
{
    TIME t(0, 0);
    DateTime = clock_var.getDateTime();

    t.set_H(DateTime.hour);
    t.set_Min(DateTime.minute);
    return (t);
}
