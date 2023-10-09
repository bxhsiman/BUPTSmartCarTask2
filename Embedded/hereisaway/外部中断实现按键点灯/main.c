#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "CounterSensor.h"

int main(void)
{
	led_init();
	CounterSensor_Init();
	
	while(1)
	{
		
	}
}
