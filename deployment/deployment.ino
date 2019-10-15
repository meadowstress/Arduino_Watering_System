//#include "mock_arduino.h" //Enable for testing
#include "time.h"
#include "PS_func.h"
#include "DHT.h"

//pins
const short PUMP = 8;
const short VALVETOP = 9;
const short VALVEBOTTOM = 10;
const short SWITCH = 7;
const short WATER = 3;
const short WATERLEVEL = 4;
const short MEASURE_WL = 5;
const short TEMPERATURE = 6; 
DHT dht(TEMPERATURE, DHT22);

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
unsigned long const t_low_temp_vol = 8000;

unsigned long const t_valve = 100;
unsigned long const t_bottom_vol = 6000;
unsigned long const t_bottom_low_temp_vol = 4000;

WaterSystem PumpControl;

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
  pinMode(WATERLEVEL, INPUT);  // Enable on Hardware
  pinMode(MEASURE_WL, OUTPUT); // Enable on Hardware
  Serial.begin(9600);  // Enable on Hardware
  dht.begin();
  

  digitalWrite(PUMP, HIGH); //default no pumping enabled
  digitalWrite(VALVETOP, HIGH); //default no pumping enabled
  digitalWrite(VALVEBOTTOM, HIGH); //default no pumping enabled

  //prevent different states when water switch is on
  if (digitalRead(WATER) == LOW) //set to LOW for Pullup resistor
  {
    pre_state_water = true;
    current_state_water = true;
  }

  timer_on = true; // software switch for pump timer function
} //Enable on Hardware




void loop() // Enable on Hardware
{ // Enable on Hardware
  if (PumpControl.isSystemSwitchedOn() && PumpControl.isWaterActivated())
  {
    PumpControl.Pump_Water(t_half_can, VALVETOP, t_valve);
  }

   //Output of Temperature for test purpose
  Serial.print("Temperatur: ");
  Serial.println(PumpControl.getTemperature());
  
  //setup timer
  TIME t_curr(17,9), t1(10,0), t2(15,0);

  if (timer_on)
  {
    Serial.println("Start Timer:");
    PumpControl.Pump_Water_Clock(t_low_temp_vol, t_bottom_low_temp_vol, t_curr, t1, t2);
  }
  
}