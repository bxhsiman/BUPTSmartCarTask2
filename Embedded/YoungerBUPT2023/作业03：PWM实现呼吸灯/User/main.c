#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Timer.h"
#include "PWM.h"
#include "Delay.h"

int main()
{
	PWM_Init();
	while(1)
	{
		int i;
		for(i = 0;i<100;i++)
		{
			PWM_SetCompare(i);
		}
		Delay_ms(100);
		for(i = 0;i<100;i++)
		{
			PWM_SetCompare(100-i);
		}
		Delay_ms(100);
	}
}
