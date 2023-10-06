#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"

uint8_t i;

int main(void)
{
	PWM_Init();

	while (1)
	{
		for (i = 0; i <= 100; i++)
		{
			PWM_SetCompare1(i);
			Delay_ms(1);
		}
		for (i = 0; i <= 80; i++)
		{
			PWM_SetCompare1(100 - i);
			Delay_ms(3);
		}
		for (i = 1; i <= 17; i++)
		{
			PWM_SetCompare1(20 - i);
			Delay_ms(25);
		}
	}
}
