#ifndef PS_FUNC_H
#define PS_FUNC_H

#include"time.h"

//pins
extern const short PUMP;
extern const short VALVETOP;
extern const short VALVEBOTTOM;
extern const short SWITCH;
extern const short WATER;
extern const short WATERLEVEL;

//states
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

extern TIME pre_pause1, pre_pause2, pause1_water, pause2_water;

//function headers
bool State_Switch(int input);
void State_Water();
bool Hold_State(unsigned long  hold_time);
void Hold_State_Clock(unsigned long  hold_time, TIME t, unsigned long pump_time);
int Pump_Water(unsigned long pump_time, unsigned short valve_pin, unsigned long valve_time);
int Pump_Water_Clock(unsigned long pump_time_top, unsigned long pump_time_bottom, TIME& t_curr, TIME& t1_water, TIME& t2_water);

#endif