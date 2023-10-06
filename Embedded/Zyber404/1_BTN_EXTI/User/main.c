#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "btn.h"

int main(void)
{
	//初始化
	LED_Init();
	btn_Init();
	
	while (1)
	{
		
	}
}
