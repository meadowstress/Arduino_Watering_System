#ifndef PS_FUNC_H
#define PS_FUNC_H

#include"time.h"

extern TIME pre_pause1, pre_pause2, pause1_water, pause2_water;

//function headers
bool State_Switch(int input);
void State_Water();
bool Hold_State(unsigned long  hold_time);
void Hold_State_Clock(unsigned long  hold_time, TIME t, unsigned long pump_time);
int Pump_Water(unsigned long pump_time, unsigned short valve_pin, unsigned long valve_time);
int Pump_Water_Clock(unsigned long pump_time_top, unsigned long pump_time_bottom, TIME& t_curr, TIME& t1_water, TIME& t2_water);

#endif