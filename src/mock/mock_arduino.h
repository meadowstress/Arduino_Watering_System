#ifndef MOCK_ARDUINO_H
#define MOCK_ARDUINO_H

#include <string>

using namespace std;

// Mocking Analog Pins

const unsigned short A0 = 14;
const unsigned short A1 = 15;
const unsigned short A2 = 16;
const unsigned short A3 = 17;
const unsigned short A4 = 18;
const unsigned short A5 = 19;

// artificial states for actuators
extern bool pump_state;
extern bool valve_state_top;
extern bool valve_state_bottom;
extern bool switch_state;
extern bool water_state;
extern bool water_level_state;
extern bool measure_current_wl;
extern float temperature_value;

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
    void println(unsigned int data);
    void print(unsigned int data);
};

extern Output Serial;

class DHT
{
 private:
    float temperature;

 public:
    DHT() { temperature = 0.0F; }
    ~DHT() {}
    float readTemperature();
};

extern DHT dht;

struct RTCDateTime
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
};

class DS3231
{
 public:
    RTCDateTime getDateTime();
    void setDateTime(unsigned int iYear,
                     unsigned int iMonth,
                     unsigned int iDay,
                     unsigned int iHour,
                     unsigned int iMinute,
                     unsigned int iSecond);
};

extern RTCDateTime current_local_time;

#endif