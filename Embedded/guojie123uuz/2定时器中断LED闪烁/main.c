#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "TimerLED.h"

uint16_t Num;

int main(void)
{
	OLED_Init();
	TimerLED_Init();
	
	OLED_ShowString(3,1,"Period:4s");
	
	while(1)
	{
		if(Num%4==1)
		{
			OLED_ShowString(1,1,"LEDState2");
			OLED_ShowString(2,1,"RedON  BlueOFF");
		}
		else if(Num%4==2)
		{
			OLED_ShowString(1,1,"LEDState3");
			OLED_ShowString(2,1,"RedOFF BlueON ");
		}
		else if(Num%4==3)
		{
			OLED_ShowString(1,1,"LEDState4");
			OLED_ShowString(2,1,"RedON  BlueON ");
		}
		else
		{
			OLED_ShowString(1,1,"LEDState1");
			OLED_ShowString(2,1,"RedOFF BlueOFF");
		}
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		Num++;
		
		if(Num%4==0)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_1);
		    GPIO_SetBits(GPIOA,GPIO_Pin_2);
		}
		else if(Num%4==2)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_1);
		    GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		}
		else
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
