#include "stm32f10x.h"                  // Device header
#include "LED.h" //按键点灯和闪烁的硬件实现
#include "OLED.h" //OLED显示屏
#include "Key.h" //外部中断实现按键控制
#include "PWM.h" 
#include "Timer.h" //定时器中断实现LED闪烁和PWM调频
#include "ADC.h" 


int main(void)
{
	LED_Init();
	OLED_Init();
	Key_Init();
	PWM_Init();
	Timer_Init();
	AD_Init();
	
	OLED_ShowString(1, 1, "ADC:");

	while (1)
	{
		OLED_ShowNum(1, 5, AD_GetValue(), 4);
	}
}
