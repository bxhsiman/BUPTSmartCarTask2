#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "LED.h"
#include "Delay.h"

int main(void)
{
	
	LED_Init();
	PWM_Init();
	uint8_t n = 0;
	
	while(1)
	{
		for (n = 0;n<100;n++)
		{
			PWM_SetCompare(n);
			Delay_ms(10);
		}
		for(n = 100;n>0;n--)
		{
			PWM_SetCompare(n);
			Delay_ms(10);
		}
	}
	
}
