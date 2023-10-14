#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"

int16_t Compare;
int16_t i;

int main(void)
{
	OLED_Init();
	PWM_Init();
	
	while (1)
	{
		//通过改变占空比来改变LED亮度
		for(i = 0; i <= 100; i++)
		{
			PWM_Setcompare1(i);
		    Delay_ms(10);
		}
		for(i = 0; i <= 100; i++)
		{
			PWM_Setcompare1(100-i);
			Delay_ms(10);
		}
	}
}
