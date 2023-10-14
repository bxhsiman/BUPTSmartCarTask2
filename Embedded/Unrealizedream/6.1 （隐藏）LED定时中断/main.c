#include "stm32f10x.h"
#include "delay.h"
#include "timer.h"
#include "led.h"
//六秒进行一次turn,以达成闪烁

int16_t Num ;

int main(void)
{
	TIMER_Init();
	LED_Init();
	
	while(1)
	{
		if(Num == 6)
		{
		LED1_TURN();
		Num = 0 ;
		}
		
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET )
	{
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}





