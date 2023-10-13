#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Key.h"
#include "Timer.h"

int main(void)
{
	LED_Init();
	Key_Init();
	Timer_Init();                        //use TIM to eliminate key jitter
	
	while(1)
	{
		
	}
}
