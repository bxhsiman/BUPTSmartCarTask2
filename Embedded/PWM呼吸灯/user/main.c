#include "public.h"
#include "pwm.h"

void main()
{
	u8 dir=0;
	u16 duty=0;
	
	pwm_init(0XFF,0XF6,100,0);
	
	while(1)
	{
		if(dir==0)
		{
			duty++;
			if(duty==70)
				dir=1;
		}
		else
		{
			duty--;
			if(duty==0)
				dir=0;
		}
		pwm_set_duty_cycle(duty);
		delay(100);
	}
}