#include "pwm.h"

u8 gtime_h;
u8 gtime_l;
u16 gtime_scale;
u16 gduty;

void pwm_init(u8 time_h,u8 time_l,u16 time_scale,u16 duty)
{
	gtime_h=time_h;
	gtime_l=time_l;
	gtime_scale=time_scale;
	gduty=duty;
	
	TMOD|=0X01;
	TH0=gtime_h;
	TL0=gtime_l;
	ET0=1;
	EA=1;
	TR0=1;
}

void pwm_set_duty_cycle(u16 duty)
{
	gduty=duty;	
}

void PWM(void) interrupt 1
{
	static u16 time=0;
	
	TH0=gtime_h;
	TL0=gtime_l;
	
	time++;
	
	if(time>=gtime_scale)
		time=0;
	if(time>=gduty)
		pwm=0;
	else
		pwm=1;
}