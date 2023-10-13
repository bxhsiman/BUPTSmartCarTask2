#include "stm32f10x.h"                  // Device header
#include "Timer.h"
#include "LED.h"

int16_t num;

int main(void)
{
	Timer_Init();
	LED_Init();
	
	while(1)
	{
		
	}
}
