#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"

uint8_t KeyNum;

int main()
{
	LED_Init();
	Key_Init();
	
	while (1)
	{
		
	}
}

