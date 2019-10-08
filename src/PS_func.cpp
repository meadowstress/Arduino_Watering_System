#include "PS_func.h"
#include "mock_arduino.h" //Enable for Testing
/*
#include <Arduino.h> //Enable on Hardware
#include <HardwareSerial.h> //Enable on Hardware
*/

//Switch logic
bool State_Switch(int input)
{
  bool state;
  // switch logic
  if (input == LOW)
  {
    state = true;
  }
  else
  {
    state = false;
  }
  return state;
}


void State_Water()
{
  if (digitalRead(WATER) == HIGH)
  {
    current_state_water = true;
  }
  else
  {
    current_state_water = false;
  }

  if (current_state_water != pre_state_water)
  {
    water_on = true;
    pre_state_water = current_state_water;
  }
  else
  {
    water_on = false;
  }
}


// Hold logic

bool Hold_State(unsigned long  hold_time)
{

  bool state_flag = true;
  unsigned long start_time = millis();
  unsigned long elapsed_time = 0;
  int i = 0;

  do
  {
    i++;
    switch_on = State_Switch(digitalRead(SWITCH));
    water_level_ok = State_Switch(digitalRead(WATERLEVEL));

    elapsed_time = (millis() - start_time);
    if ( (elapsed_time > hold_time) || switch_on == false || 
    water_level_ok == false)
    {
      state_flag = false;
    }
  } while (state_flag);

  // test if hold time has been elapsed regularly
  // var i is only necessary for time simulation with high factors
  if((elapsed_time > hold_time) && i > 1)
    return true;
  else
    return false;
}

int Pump_Water(unsigned long pump_time, unsigned short valve_pin, 
unsigned long valve_time)
{
  bool water_flag = false;

  switch_on = State_Switch(digitalRead(SWITCH));
  water_level_ok = State_Switch(digitalRead(WATERLEVEL));

  if(switch_on && water_level_ok)
  {
    Serial.println("Open Valve!");
    digitalWrite(valve_pin, LOW);
    Hold_State(valve_time);

    Serial.println("Pump Water!");
    digitalWrite(PUMP, LOW); //pumping starts
    water_flag = Hold_State(pump_time);
    digitalWrite(PUMP, HIGH); // pumping ends

    digitalWrite(valve_pin, HIGH); //closing Valve
    water_on = false; // state for interupt!
  }

  if(water_flag==true)
    return(1);
  else
    return(0);
}

int WaterSystem::Hold_State_Clock(unsigned long  hold_time, TIME t, unsigned long pump_time)
{
  int water_activations = 0;
  
  Serial.println("Clock: hold_time:");
  Serial.println(hold_time);
  t.print();

  bool state_flag = true;
  unsigned long start_time = millis();

  do
  {
    if ((millis() - start_time > hold_time) )
    {
      state_flag = false;
    }
    
    if (isWaterActivated() && isWaterLevelOk())
    {
      water_activations += Pump_Water(pump_time, VALVETOP, t_valve);
    }

  } while (state_flag);
  return water_activations;
}

int WaterSystem::Pump_Water_Clock(unsigned long pump_time_top, 
unsigned long pump_time_bottom, TIME& t_curr, TIME& t1_water, TIME& t2_water)
{
  int water_counter = 0;
  TIME eleven_pm(23, 0), one_am(1, 0);
  unsigned long pTime = 0;

  if (t1_water <= t2_water)
  {
    pause1_water = t2_water - t1_water;
    pause2_water = ((eleven_pm - t2_water) + one_am) + t1_water;
  }
  else if (t1_water > t2_water)
  {
    pause1_water = t1_water - t2_water;
    pause2_water = ((eleven_pm - t1_water) + one_am) + t2_water;
  }
  else
    Serial.println("Fehler bei Berechnung von pause1_water und pause2_water!");

  //Kontrollausgaben für Timer
  Serial.println("pause1_water:");
  Serial.println(pause1_water.Time2Ticks());
  pause1_water.print();
  Serial.println("pause2_water:");
  Serial.println(pause2_water.Time2Ticks());
  pause2_water.print();

  if (t_curr <= t1_water)
  {
    pre_pause1 = t1_water - t_curr;

    Serial.println("pre_pause1:");
    Serial.println(pre_pause1.Time2Ticks());
    pre_pause1.print();

    Hold_State_Clock(pre_pause1.Time2Ticks(), pre_pause1, t_half_can);
  }

  else if (t_curr > t1_water && t_curr <= t2_water)
  {
    pre_pause1 = t2_water - t_curr;
    pre_pause2 = ((eleven_pm - t2_water) + one_am) + t1_water;

    Serial.println("pre_pause1:");
    Serial.println(pre_pause1.Time2Ticks());
    pre_pause1.print();

    Serial.println("pre_pause2:");
    Serial.println(pre_pause2.Time2Ticks());
    pre_pause2.print();

    Hold_State_Clock(pre_pause1.Time2Ticks(), pre_pause1, t_half_can);

    pTime = 0;
    switch_on = isSystemSwitchedOn();
    water_level_ok = isWaterLevelOk();
    if (switch_on && water_level_ok)
    {
      water_counter += Pump_Water(pump_time_top, VALVETOP, t_valve);
      water_counter += Pump_Water(pump_time_bottom, VALVEBOTTOM, t_valve);
      pTime = pump_time_top + pump_time_bottom + 2L * t_valve;
    }

    Hold_State_Clock(pre_pause2.Time2Ticks() - pTime, pre_pause2, t_half_can);
  }

  else if (t_curr > t2_water)
  {
    pre_pause1 = ((eleven_pm - t_curr) + one_am) + t1_water;

    Serial.println("pre_pause1:");
    Serial.println(pre_pause1.Time2Ticks());
    pre_pause1.print();

    Hold_State_Clock(pre_pause1.Time2Ticks(), pre_pause1, t_half_can);
  }

  else
    Serial.println("Fehler bei Berechnung von pre_pause!");
  
  
  for(int i=0; i < 2; i++) // Enable for Testing
  { // Enable for Testing
  

  /*
  while (timer_on) //Enalbe on Hardware
  { // Enable on Hardware
  */

    switch_on = isSystemSwitchedOn();
    water_level_ok = isWaterLevelOk();

    pTime = 0;
    if (switch_on && water_level_ok)
    {
      water_counter += Pump_Water(pump_time_top, VALVETOP, t_valve);
      water_counter += Pump_Water(pump_time_bottom, VALVEBOTTOM, t_valve);
      pTime = pump_time_top + pump_time_bottom + 2L * t_valve;
    }

    Hold_State_Clock(pause1_water.Time2Ticks() - pTime, pause1_water, t_half_can);

    switch_on = isSystemSwitchedOn();
    water_level_ok = isWaterLevelOk();

    pTime = 0;
    if (switch_on && water_level_ok)
    {
      water_counter += Pump_Water(pump_time_top, VALVETOP, t_valve);
      water_counter += Pump_Water(pump_time_bottom, VALVEBOTTOM, t_valve);
      pTime = pump_time_top + pump_time_bottom + 2L * t_valve;
    }

    Hold_State_Clock(pause2_water.Time2Ticks() - pTime, pause2_water, t_half_can);
  }
  return(water_counter);
}

bool WaterSystem::isWaterLevelOk()
{
    bool level_Ok = false;
    digitalWrite(MEASURE_WL, LOW); //measurement current switched on
    level_Ok = (bool)digitalRead(WATERLEVEL);
    digitalWrite(MEASURE_WL, HIGH); //measurement current switched off
    return(level_Ok);
}

bool WaterSystem::isSystemSwitchedOn()
{
  bool state = false;
  state = (bool)digitalRead(SWITCH);
  if (state == LOW)
    return true;
  else
    return false;
}

bool WaterSystem::isWaterActivated()
{
  if (digitalRead(WATER) == HIGH)
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