#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Timer.h"
#include "OLED.h"

int main()
{
	int16_t judge;
	
	Timer_Init();
	LED_Init();
	OLED_Init();
	
	while(1)
	{
		judge = Num_Get();
		
		if(judge == 1)
		{
			LED1_ON();
			OLED_ShowNum(1,5,1,1);
		}
		else if(judge == -1)
		{
			LED1_OFF();
			OLED_ShowNum(1,5,0,1);
		}
	}
}
