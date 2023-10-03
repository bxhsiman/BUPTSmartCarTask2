#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"


int main(void)
{
	
	Key_Init();
	LED_Init(GPIO_Pin_0);
	OLED_Init();
	
	while(1)
	{
		EXTI0_IRQHandler();
	}
		
}
