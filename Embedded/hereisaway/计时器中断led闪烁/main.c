#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "tim.h"

int main(void)
{
	Tim_init();
	led_init();
	
	while(1)
	{
		
	}
}
