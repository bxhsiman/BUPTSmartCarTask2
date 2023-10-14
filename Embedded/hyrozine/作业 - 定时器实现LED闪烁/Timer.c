#include "stm32f10x.h"                  // Device header
#include "LED.h"

extern int16_t num;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBasInitStructure;
	TIM_TimeBasInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBasInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBasInitStructure.TIM_Period = 1000 - 1;     
	TIM_TimeBasInitStructure.TIM_Prescaler = 7200 - 1;   
	TIM_TimeBasInitStructure.TIM_RepetitionCounter = 0;  
	TIM_TimeBaseInit(TIM2,&TIM_TimeBasInitStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		 LED_Turn();
		 num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}






