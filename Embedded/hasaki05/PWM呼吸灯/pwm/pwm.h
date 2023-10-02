#ifndef _pwm_h
#define _pwm_h

#include "public.h"

void pwm_init(u8 time_h,u8 time_l,u16 time_scale,u16 duty);
void pwm_set_duty_cycle(u16 duty);

sbit pwm=P2^1;
extern u16 gtime_scale;


#endif