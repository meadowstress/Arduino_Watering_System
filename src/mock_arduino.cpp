#include <sys/timeb.h>
#include "mock_arduino.h"
#include <iostream>

using namespace std;

// artificial states for actuators
bool pump_state = false;
bool valve_state_top = false;
bool valve_state_bottom = false;
bool switch_state = false;
bool water_state = false;

const bool HIGH = false;
const bool LOW = true;

Output Serial;

timeb t_start;


unsigned long millis() 
{
  timeb t_now;
  ftime(&t_now);
  unsigned long ms = (t_now.time  - t_start.time) * 1000 + (t_now.millitm - t_start.millitm);
  ms = ms * 100000; //simulate time faster
  //return (t_now.time  - t_start.time) * 1000 + (t_now.millitm - t_start.millitm);
  return(ms);
}

void digitalWrite(const short& pin, const bool& state)
{
  if(pin == PUMP)
  {
    if(state == HIGH)
      pump_state = false;
    else if(state == LOW)
      pump_state = true;
    else
      std::cout << "Throw Error: digitalWrite(PUMP)\n";
  }

  else if( pin ==  VALVETOP)
  {
    if(state == HIGH)
      valve_state_top = false;
    else if(state == LOW)
      valve_state_top = true;
    else
      std::cout << "Throw Error: digitalWrite(VALVETOP)\n";
  }

  else if( pin ==VALVEBOTTOM)
  {
    if(state == HIGH)
      valve_state_bottom = false;
    else if(state == LOW)
      valve_state_bottom = true;
    else
      std::cout << "Throw Error: digitalWrite(VALVEBOTTOM)\n";
  }
}

bool digitalRead(const short& pin)
{
  if(pin == PUMP)
    return(pump_state);

  else if( pin ==  VALVETOP)
    return(valve_state_top);

  else if( pin ==VALVEBOTTOM)
    return(valve_state_bottom);

  else if(pin == SWITCH)
    return(switch_state);

  else if (pin == WATER)
    return(water_state);
  else 
    cout << "Throw Error: digitalRead \n";
}

void Output::print(string data)
{
  cout << data;
}

void Output::println(string data)
{
  cout << data <<endl;
}

void Output::print(long data)
{
  cout << data;
}

void Output::println(long data)
{
  cout << data <<endl;
}

void Output::print(unsigned long data)
{
  cout << data;
}

void Output::println(unsigned long data)
{
  cout << data <<endl;
}

void Output::print(float data)
{
  cout << data;
}

void Output::println(float data)
{
  cout << data <<endl;
}