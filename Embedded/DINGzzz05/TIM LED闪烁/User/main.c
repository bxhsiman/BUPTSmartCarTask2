#include "stm32f10x.h"                  // Device header
#include "TIMer.h"
#include "LED.h"

int main(void)
{
	
	LED_Init();
	Timer_Init();
	
	while(1)
	{
		TIM2_IRQHandler();
	}
	
}
