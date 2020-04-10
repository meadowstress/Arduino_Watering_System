#include <sys/timeb.h>
#include "mock_arduino.h"
#include <iostream>
#include <ctime>

using namespace std;

// artificial states for actuators
bool pump_state = false;
bool valve_state_top = false;
bool valve_state_bottom = false;
bool switch_state = true;
bool water_state = false;
bool water_level_state = false;
bool measure_current_wl = false;
float temperature_value = 20;

//artificial local time
RTCDateTime current_local_time{2020, 04, 06, 11, 30, 00};

/*
This definition of HIGH and LOW is very volatile and is only valid for 
switches connected to pulldown resistors. Currently there are 3 switches
implemented in the code.
*/

const bool HIGH = false;
const bool LOW = true;

Output Serial;
DHT dht;

timeb t_start;

unsigned long millis()
{
  timeb t_now;
  ftime(&t_now);
  unsigned long ms = (t_now.time - t_start.time) * 1000 + (t_now.millitm - t_start.millitm);
  ms = ms * 100000; //simulate time faster
  //return (t_now.time  - t_start.time) * 1000 + (t_now.millitm - t_start.millitm);
  return (ms);
}

void digitalWrite(const short &pin, const bool &state)
{
  if (pin == PUMP)
  {
    if (state == HIGH)
      pump_state = false;
    else if (state == LOW)
      pump_state = true;
    else
      std::cout << "Throw Error: digitalWrite(PUMP)\n";
  }

  else if (pin == VALVETOP)
  {
    if (state == HIGH)
      valve_state_top = false;
    else if (state == LOW)
      valve_state_top = true;
    else
      std::cout << "Throw Error: digitalWrite(VALVETOP)\n";
  }

  else if (pin == VALVEBOTTOM)
  {
    if (state == HIGH)
      valve_state_bottom = false;
    else if (state == LOW)
      valve_state_bottom = true;
    else
      std::cout << "Throw Error: digitalWrite(VALVEBOTTOM)\n";
  }

  else if (pin == WATERLEVEL)
  {
    if (state == HIGH)
      water_level_state = false;
    else if (state == LOW)
      water_level_state = true;
    else
      std::cout << "Throw Error: digitalWrite(WATERLEVEL)\n";
  }

  else if (pin == MEASURE_WL)
  {
    if (state == HIGH)
      measure_current_wl = false;
    else if (state == LOW)
      measure_current_wl = true;
    else
      std::cout << "Throw Error: digitalWrite(MEASURE_WL)\n";
  }
}

bool digitalRead(const short &pin)
{
  if (pin == PUMP)
    return (pump_state);

  else if (pin == VALVETOP)
    return (valve_state_top);

  else if (pin == VALVEBOTTOM)
    return (valve_state_bottom);

  else if (pin == SWITCH)
    return (switch_state);

  else if (pin == WATER)
    return (water_state);

  else if (pin == WATERLEVEL)
    return (water_level_state && measure_current_wl);

  else if (pin == MEASURE_WL)
    return (measure_current_wl);

  else
    cout << "Throw Error: digitalRead \n";
}

void Output::print(string data)
{
  cout << data;
}

void Output::println(string data)
{
  cout << data << endl;
}

void Output::print(long data)
{
  cout << data;
}

void Output::println(long data)
{
  cout << data << endl;
}

void Output::print(unsigned long data)
{
  cout << data;
}

void Output::println(unsigned long data)
{
  cout << data << endl;
}

void Output::print(unsigned int data)
{
  cout << data;
}

void Output::println(unsigned int data)
{
  cout << data << endl;
}

void Output::print(float data)
{
  cout << data;
}

void Output::println(float data)
{
  cout << data << endl;
}

float DHT::readTemperature()
{
  return (temperature_value);
}

void DS3231::setDateTime(unsigned int iYear, unsigned int iMonth,
                         unsigned int iDay, unsigned int iHour, unsigned int iMinute,
                         unsigned int iSecond)
{
  current_local_time.year = iYear;
  current_local_time.month = iMonth;
  current_local_time.day = iDay;
  current_local_time.hour = iHour;
  current_local_time.minute = iMinute;
  current_local_time.second = iSecond;
}

RTCDateTime DS3231::getDateTime()
{

  //  mocking with computer system time
  // time_t current_time_epoch = time(0);
  // tm *current_local_time = localtime(&current_time_epoch);

  RTCDateTime t;

  // set return value
  t.year = current_local_time.year;
  t.month = current_local_time.month;
  t.day = current_local_time.day;
  t.hour = current_local_time.hour;
  t.minute = current_local_time.minute;
  t.second = current_local_time.second;

  return t;
}