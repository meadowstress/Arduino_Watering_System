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
extern const short MEASURE_WL;

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

//function headers
bool State_Switch(int input);
void State_Water();
bool Hold_State(unsigned long  hold_time);
void Hold_State_Clock(unsigned long  hold_time, TIME t,
unsigned long pump_time);

int Pump_Water(unsigned long pump_time, unsigned short valve_pin,
unsigned long valve_time);

class WaterSystem
{
    private:

    TIME pre_pause1;
    TIME pre_pause2;
    TIME pause1_water;
    TIME pause2_water;

    public:
        WaterSystem()
        {
            pre_pause1.set_Time(0,0);
            pre_pause2.set_Time(0,0);
            pause1_water.set_Time(0,0);
            pause2_water.set_Time(0,0);
        }
        ~WaterSystem(){}
    
    int Pump_Water_Clock(unsigned long pump_time_top,
    unsigned long pump_time_bottom, TIME& t_curr, TIME& t1_water, TIME& t2_water);

    TIME get_pre_pause1(){return pre_pause1;}
    TIME get_pre_pause2(){return pre_pause2;}
    TIME get_pause1_water(){return pause1_water;}
    TIME get_pause2_water(){return pause2_water;}

};

#endif