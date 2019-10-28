//#include "mock_arduino.h" //Enable for testing
#include "time.h"
#include "PS_func.h"

//pins
const short PUMP = 8;
const short VALVETOP = 9;
const short VALVEBOTTOM = 10;
const short SWITCH = 7;
const short WATER = 3;
/*
Set to 7 meaning the same pin like the on/off switch to disable functionality
of waterlevel functionality. Set to 4 when intended to use this functionality. 
*/
const short WATERLEVEL = 7; 

//states
bool pre_state_water = false;
bool current_state_water = false;
bool switch_on = false;
bool water_on = false;
bool timer_on = false;
bool water_level_ok = false;

unsigned long const t_half_can = 15000;
unsigned long const t_half_vol = 40000;
unsigned long const t_quater_vol = 20000;
unsigned long const t_low_temp_vol = 6000;

unsigned long const t_valve = 100;
unsigned long const t_bottom_vol = 6000;
unsigned long const t_bottom_low_temp_vol = 2000;

/*
int main(void) //Enable for Testing
{ // Enable for Testing
*/


void setup() // Enable on Hardware
{
  pinMode(PUMP, OUTPUT);  // Enable on Hardware
  pinMode(VALVETOP, OUTPUT);  // Enable on Hardware
  pinMode(VALVEBOTTOM, OUTPUT);  // Enable on Hardware
  pinMode(SWITCH, INPUT);  // Enable on Hardware
  pinMode(WATER, INPUT);  // Enable on Hardware
  /*
  since waterlevel feature not inteded to use configuration of waterlevel pin
  skiped.
  */
  //pinMode(WATERLEVEL, INPUT);  // Enable on Hardware
  Serial.begin(9600);  // Enable on Hardware
  

  digitalWrite(PUMP, HIGH); //default no pumping enabled
  digitalWrite(VALVETOP, HIGH); //default no pumping enabled
  digitalWrite(VALVEBOTTOM, HIGH); //default no pumping enabled

  //prevent different states when water switch is on
  if (digitalRead(WATER) == HIGH)
  {
    pre_state_water = true;
    current_state_water = true;
  }
} //Enable on Hardware




void loop() // Enable on Hardware
{ // Enable on Hardware

  
  //configuration settings - change time here
  timer_on = true; // software switch for pump timer function

  // state logics
  switch_on = State_Switch(digitalRead(SWITCH));
  State_Water();

  // function execution
  if (switch_on && water_on)
  {
    Serial.println("pumpWater single Function!");
    pumpWater(t_half_can, VALVETOP, t_valve);
    pumpWater(t_bottom_vol, VALVEBOTTOM, t_valve);
  }

  //setup timer
  TIME t_curr(8, 51), t1(10, 0), t2(15, 0);

  if (timer_on)
  {
    Serial.println("Start Timer:");
    Pump_Water_Clock(t_low_temp_vol, t_bottom_low_temp_vol, t_curr, t1, t2);
  }
}