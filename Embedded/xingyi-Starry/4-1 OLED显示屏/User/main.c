#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "PWM.h"
#include "Timer.h"


int main(void)
{
	LED_Init();
	OLED_Init();
	Key_Init();
	PWM_Init();
	Timer_Init();
	
	while (1)
	{

	}
}
