#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Timer.h"
#include "LED.h"

int main(void)
{
	//初始化
	LED_Init();
	Timer_Init();
	
	while (1)
	{
		
	}
}
