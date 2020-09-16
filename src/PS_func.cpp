#include "PS_func.h"
#include "mock_arduino.h"  //Enable for Testing
#include "parameter.h"
#include <string.h>
/*
#include <Arduino.h>         //Enable on Hardware
#include <HardwareSerial.h>  //Enable on Hardware
#include "DHT.h"             //Enable on Hardware
#include <Wire.h>            //Enable on Hardware
#include <DS3231.h>          //Enable on Hardware
#include <SPI.h>
#include <SD.h>
*/
bool WaterSystem::checkSystem()
{
    bool system_status = (sd_card_ok && water_level_ok);

    if (system_status)
    {
        digitalWrite(par::LED, LOW);
    }

    else
    {
        digitalWrite(par::LED, HIGH);
    }

    return (system_status);
}

bool WaterSystem::isSDCardOk()
{
    bool isSDCardOk = SD.begin(par::CHIPSELECT);

    if (isSDCardOk)
    {
        sd_card_ok = true;
    }
    else
    {
        sd_card_ok = false;
    }

    checkSystem();
    return (isSDCardOk);
}

String WaterSystem::getSDFileName()
{
    // using global time variable for date

    // just take the last 2 digits of the year
    unsigned int y = DateTime.year % 100;
    /*
        String year  = String(y);               // Enable on Hardware
        String month = String(DateTime.month);  // Enable on Hardware
        String day   = String(DateTime.day);    // Enable on Hardware
    */

    String year  = to_string(y);               // Enable for Testing
    String month = to_string(DateTime.month);  // Enable for Testing
    String day   = to_string(DateTime.day);    // Enable for Testing

    // always have two digits for month e.g. 06
    if (DateTime.month < 10)
    {
        month = "0" + month;
    }
    else
    {
        // do nothing
    }

    // always have two digits for day e.g. 07
    if (DateTime.day < 10)
    {
        day = "0" + day;
    }
    else
    {
        // do nothing
    }

    // date format year-month-day e.g. 20-06-07
    String fname = year + "-" + month + "-" + day + ".txt";
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

void WaterSystem::printlnToSDFile(const String input)
{
    File logFile;
    String fname = getSDFileName();
    if (isSDCardOk())
    {
        logFile = SD.open(fname, FILE_WRITE);
        logFile.print(input);
        logFile.print("\n");
        logFile.close();
    }
    else
    {
        Serial.println("\nWriting to SD Card not successful!\n");
    }
}

void WaterSystem::printToSDFile(const int input)
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

void WaterSystem::printlnToSDFile(const int input)
{
    File logFile;
    String fname = getSDFileName();

    if (isSDCardOk())
    {
        logFile = SD.open(fname, FILE_WRITE);
        logFile.print(input);
        logFile.print("\n");
        logFile.close();
    }
    else
    {
        Serial.println("\nWriting to SD Card not successful!\n");
    }
}

// support function
void printSystemInfo()
{
    TIME t1(0, 0, 0), t2(0, 0, 0);
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
    Serial.print(F(":"));
    Serial.print(DateTime.second);
    Serial.print(F("   "));

    // Temperature
    Serial.print(F("Temperature = "));
    Serial.print(PumpControl.getTemperature());
    Serial.print(F(" Celsius\n"));

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

    ms = PumpControl.isWaterLevelOk();
    Serial.print(F("isWaterLevelOk = "));
    Serial.println(ms);
    // distance to next cyclic message
    Serial.println(F(""));
}

void logSDData()
{
    TIME t1(0, 0, 0), t2(0, 0, 0);
    unsigned int ms = 0;

    Serial.print(F("\nWriting to SD...\n"));

    // Currently selected Temperature Range
    PumpControl.printToSDFile(DateTime.day);
    PumpControl.printToSDFile(F("."));
    PumpControl.printToSDFile(DateTime.month);
    PumpControl.printToSDFile(F("."));
    PumpControl.printToSDFile(DateTime.year);
    PumpControl.printToSDFile(F(": "));
    PumpControl.printToSDFile(DateTime.hour);
    PumpControl.printToSDFile(F(":"));
    PumpControl.printToSDFile(DateTime.minute);
    PumpControl.printToSDFile(F(":"));
    PumpControl.printToSDFile(DateTime.second);
    PumpControl.printToSDFile(F("   "));

    PumpControl.printToSDFile(F("Temperature = "));
    PumpControl.printToSDFile(PumpControl.getTemperature());
    PumpControl.printToSDFile(F(" Celsius\n"));

    PumpControl.printToSDFile(F("Watering Parameters: "));
    PumpControl.printToSDFile(F("t1_water = "));
    t1 = par::t1_water;
    t1.printSD();  // print function not defined for const times

    PumpControl.printToSDFile(F("; "));
    PumpControl.printToSDFile(F("t2_water = "));
    t2 = par::t2_water;
    t2.printlnSD();  // print function not defined for const times

    ms = PumpControl.getWaterTimeTop();
    PumpControl.printToSDFile(F("Current chosen ms for top watering: "));
    PumpControl.printlnToSDFile(ms);

    ms = PumpControl.getWaterTimeBottom();
    PumpControl.printToSDFile(F("Current chosen ms for bottom watering: "));
    PumpControl.printlnToSDFile(ms);
    PumpControl.printlnToSDFile("");

    ms = PumpControl.isWaterLevelOk();
    PumpControl.printToSDFile(F("isWaterLevelOk = "));
    PumpControl.printToSDFile(ms);

    Serial.print(F("...writing to SD finished!\n"));
}

void logSystemInfo()
{
    if (PumpControl.isLoggingIntervallPassed())
    {
        printSystemInfo();

        if (!PumpControl.getSwitchState())
        {
            logSDData();
        }
    }
    else
    {
        // do nothing
    }
}

// Hold logic
bool WaterSystem::holdState(unsigned int hold_time)
{
    unsigned long start_time   = millis();
    unsigned long elapsed_time = 0;
    unsigned long i            = 0;

    switch_on = isSystemSwitchedOn();

    while ((elapsed_time < hold_time) && switch_on)
    {
        i++;
        switch_on    = isSystemSwitchedOn();
        elapsed_time = (millis() - start_time);
    }

    // test if hold time has been elapsed regularly
    // var i is only necessary for time simulation with high factors
    if ((elapsed_time > hold_time) && i >= 1)
        return true;
    else
        return false;
}

int WaterSystem::pumpWater(unsigned int pump_time,
                           byte valve_pin,
                           byte valve_time)
{
    bool water_flag = false;

    Serial.println(F("\n\nOpen Valve!"));

    digitalWrite(valve_pin, LOW);
    holdState(valve_time);

    Serial.println(F("Pump Water!"));

    digitalWrite(par::PUMP, LOW);  // pumping starts
    water_flag = holdState(pump_time);
    digitalWrite(par::PUMP, HIGH);  // pumping ends

    holdState(valve_time);
    Serial.println(F("Close Valve!\n"));
    digitalWrite(valve_pin, HIGH);  // closing Valve
    water_on = false;               // state for interupt

    // log data to SD card
    printlnToSDFile(F("\n\nOpen Valve!"));
    printlnToSDFile(F("Pump Water!"));
    printlnToSDFile(F("Close Valve!\n"));

    if (water_flag == true)
        return (1);
    else
        return (0);
}

int WaterSystem::pumpWaterManual()
{
    int water_flag = 0;

    switch_on = isSystemSwitchedOn();
    water_on  = isWaterActivated();
    isWaterLevelOk();

    if (switch_on && water_on)
    {
        if (water_level_ok)
        {
            Serial.println("\nManual Watering is enabled!\n");

            water_flag =
                pumpWater(par::t_half_can, par::VALVETUBE, par::t_valve);

            printlnToSDFile(F("\nManual Watering is enabled!\n"));
        }
        else
        {
            Serial.print("\n\nWater Level Detection Feature "
                         "deactivated Watering!\n\n");
            printToSDFile("\n\nWater Level Detection Feature "
                          "deactivated Watering!\n\n");
        }
        logSDData();
    }

    return (water_flag);
}

int WaterSystem::pumpWaterClock()
{
    int water_counter = 0;
    watering_enabled  = isAutomaticWateringEnabled();
    switch_on         = isSystemSwitchedOn();
    isWaterLevelOk();

    if (getCurrentLocalTime() == par::t1_water ||
        getCurrentLocalTime() == par::t2_water)
    {

        if (switch_on && watering_enabled && water_level_ok)
        {
            Serial.println("\nAutomatic Watering is enabled!\n");

            DateTime = clock_var.getDateTime();

            water_counter +=
                pumpWater(getWaterTimeTop(), par::VALVETOP, par::t_valve);
            water_counter +=
                pumpWater(getWaterTimeBottom(), par::VALVEBOTTOM, par::t_valve);

            // log data
            printSystemInfo();
            printlnToSDFile(F("\nAutomatic Watering is enabled!\n"));
        }

        else if (!water_level_ok)
        {
            Serial.print("\n\nWater Level Detection Feature "
                         "deactivated Watering!\n\n");
            printToSDFile("\n\nWater Level Detection Feature "
                          "deactivated Watering!\n\n");
        }

        else if (!watering_enabled)
        {
            Serial.print(
                "\n\nAutomatic Watering disabled! - Temperature too low!\n\n");
            printToSDFile(
                "\n\nAutomatic Watering disabled! - Temperature too low!\n\n");
        }

        else if (!switch_on)
        {
            Serial.print("\n\nSystem switched off!\n\n");
            printToSDFile("\n\nSystem switched off!\n\n");
        }

        else
        {
            Serial.print("\n\nUnexpected Error!\n\n");
            printToSDFile("\n\nUnexpected Error!\n\n");
        }

        // log data every time when configured watering times are reached
        logSDData();
    }

    return (water_counter);
}

bool WaterSystem::isWaterLevelOk()
{
    bool level_Ok = false;

    level_Ok = digitalRead(par::WATERLEVEL);

    if (level_Ok == HIGH)
    {
        water_level_ok = true;
        return true;
    }
    else
    {
        water_level_ok = false;
        return false;
    }
}

bool WaterSystem::isSystemSwitchedOn()
{
    bool state = false;
    state      = (bool)digitalRead(par::SWITCH);
    if (state == LOW)
    {
        return true;
    }
    else
    {
        return false;
    }
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

    if (getTemperature() >= par::lowTemp)
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
    TIME t(0, 0, 0);
    DateTime = clock_var.getDateTime();

    t.set_H(DateTime.hour);
    t.set_Min(DateTime.minute);
    t.set_Sec(DateTime.second);
    return (t);
}

bool WaterSystem::isLoggingIntervallPassed()
{
    if ((global_counter % 4000) == 0)
    {
        global_counter++;
        return true;
    }
    else
    {
        global_counter++;
        return false;
    }
}