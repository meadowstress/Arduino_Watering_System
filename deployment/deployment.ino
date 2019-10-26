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


WaterSystem PumpControl;
RTCDateTime DateTime;
/*
int main(void) //Enable for Testing
{ // Enable for Testing
for(int i = 0; i < 2; i++) //enable for Testing
{ //enable for Testing
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
  
  //set external time
  //PumpControl.setCurrentLocalTime(2019, 10, 26, 22, 53, 10);

  Serial.println("\n\nStart of Program:");
  Serial.println("-----------------\n");
} //Enable on Hardware




void loop() // Enable on Hardware
{ // Enable on Hardware

  DateTime = PumpControl.getCurrentLocalDateTime();
  Serial.print(DateTime.day);
  Serial.print(".");
  Serial.print(DateTime.month);
  Serial.print(".");
  Serial.print(DateTime.year);
  Serial.print(": ");
  Serial.print(DateTime.hour);
  Serial.print(":");
  Serial.print(DateTime.minute);
  Serial.print("   ");
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
    PumpControl.Pump_Water(par::t_half_can, VALVETOP, par::t_valve);
    //PumpControl.Pump_Water(t_bottom_vol, VALVEBOTTOM, t_valve);
  }

  if (timer_on)
  {
    Serial.println("Start Timer:");
    PumpControl.Pump_Water_Clock();
  }

  //} // Enable for Testing
}