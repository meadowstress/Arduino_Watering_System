//#include "mock_arduino.h" //Enable for testing
#include "time.h"
#include "PS_func.h"
#include "parameter.h"

//pins
const short PUMP = 8;
const short VALVETOP = 9;
const short VALVEBOTTOM = 10;
const short SWITCH = 7;
const short WATER = 3;
const short WATERLEVEL = 4;
const short MEASURE_WL = 5;
const short TEMPERATURE = 6;
DHT dht(TEMPERATURE, DHT22); //Enable for Hardware

//states
bool pre_state_water = false;
bool current_state_water = false;
bool switch_on = false;
bool water_on = false;
bool timer_on = false;
bool water_level_ok = false;

unsigned long const t_half_can = 15000;
unsigned long const t_vol = 60000;
unsigned long const t_half_vol = 40000;
unsigned long const t_quater_vol = 20000;
unsigned long const t_valve = 100;

unsigned long const t_bottom_vol = 6000;
unsigned long const t_bottom_low_temp_vol = 1000;

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
  pinMode(SWITCH, INPUT_PULLUP);  // Enable on Hardware
  pinMode(WATER, INPUT_PULLUP);  // Enable on Hardware
  pinMode(WATERLEVEL, INPUT_PULLUP);  // Enable on Hardware
  Serial.begin(9600);  // Enable on Hardware
  dht.begin();

  digitalWrite(PUMP, HIGH); //default no pumping enabled
  digitalWrite(VALVETOP, HIGH); //default no pumping enabled
  digitalWrite(VALVEBOTTOM, HIGH); //default no pumping enabled

  //prevent different states when water switch is on
  if (digitalRead(WATER) == LOW)
  {
    pre_state_water = true;
    current_state_water = true;
  }
} //Enable on Hardware




void loop() // Enable on Hardware
{ // Enable on Hardware

  Serial.println("\n\nStart of Program:");
  Serial.println("-----------------\n");
  Serial.print("Temperature = ");
  Serial.print(PumpControl.getTemperature());
  Serial.println(" Celsius");

  //configuration settings - change time here
  timer_on = true; // software switch for pump timer function

  // state logics
  switch_on = PumpControl.isSystemSwitchedOn();
  water_on = PumpControl.isWaterActivated();

  // function execution
  if (switch_on && water_on)
  {
    Serial.println("Pump_Water single Function!");
    PumpControl.Pump_Water(t_half_can, VALVETOP, t_valve);
    PumpControl.Pump_Water(t_bottom_vol, VALVEBOTTOM, t_valve);
  }

  //setup timer
  TIME t_curr(12, 32), t1(11, 30), t2(15, 30);

  if (timer_on)
  {
    Serial.println("Start Timer:");
    PumpControl.Pump_Water_Clock(t_curr, t1, t2);
  }
}