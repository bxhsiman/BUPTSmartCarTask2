#include "stm32f10x.h"
#include "led.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Timer.h"
#include "PWM.h"
#include "ADC.h"

uint8_t i;

int main(void)
{
	OLED_Init();

	LED_Init(GPIO_Pin_1); // PB1
	Key_Init();			  // PB15
	Timer_Init();
	PWM_Init();	 // PA6
	ADC1_Init(); // PA0

	while (1)
	{
		// PWM呼吸灯测试(PA6)
		for (i = 0; i < 100; i++)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
		for (i = 99; i > 0; i--)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}

		// OLED显示ADC1采样值
		OLED_ShowNum(1, 1, ADC1_GetValue(), 4);
	}
}

/// @brief 定时器中断实现LED闪烁
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		LED_Switch();								// 切换led状态
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 清除中断标志位
	}
}

/// @brief 外部中断实现按键功能,当按键按下时LED切换状态，该中断优先级高于定时器中断
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line15) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == 0)
		{
			LED_Switch(); // 切换led状态
		}
		EXTI_ClearITPendingBit(EXTI_Line15); // 清除中断标志位
	}
}
