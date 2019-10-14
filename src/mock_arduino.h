#ifndef MOCK_ARDUINO_H
#define MOCK_ARDUINO_H

#include<string>

using namespace std;

// artificial states for actuators
extern bool pump_state;
extern bool valve_state_top;
extern bool valve_state_bottom;
extern bool switch_state;
extern bool water_state;
extern bool water_level_state;
extern bool measure_current_wl;

extern const bool HIGH;
extern const bool LOW;

extern const short PUMP;
extern const short VALVETOP;
extern const short VALVEBOTTOM;

extern const short SWITCH;
extern const short WATER;
extern const short WATERLEVEL;
extern const short MEASURE_WL;

extern bool pre_state_water;
extern bool current_state_water;
extern bool switch_on;
extern bool water_on;
extern bool timer_on;
extern bool water_level_ok;

extern unsigned long const t_half_can;
extern unsigned long const t_half_vol;
extern unsigned long const t_quater_vol;
extern unsigned long const t_valve;
extern unsigned long const t_bottom_vol;

unsigned long millis();
void digitalWrite(const short& pin, const bool& state);
bool digitalRead(const short& pin);

class Output
{
    public:
        void print(string data);
        void println(string data);
        void print(long data);
        void println(long data);
        void print(unsigned long data);
        void println(unsigned long data);
        void print(float data);
        void println(float data);
};

extern Output Serial;

class DHT
{
  public:
  float temperature;
  DHT()
  {
    temperature = 0.0F;
  }
  ~DHT(){}
  float readTemperature();
};

extern DHT dht;

#endif