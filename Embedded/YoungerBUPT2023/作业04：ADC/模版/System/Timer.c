#include "stm32f10x.h"                  // Device header

uint16_t Num;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_Init_Structure);
	
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x00);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBase_Init_Structure;
	
	TIM_TimeBase_Init_Structure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBase_Init_Structure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBase_Init_Structure.TIM_Period = 5-1;
	TIM_TimeBase_Init_Structure.TIM_Prescaler = 1-1;
	TIM_TimeBase_Init_Structure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBase_Init_Structure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_Init_Structure;
	
	NVIC_Init_Structure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_Init_Structure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_Init_Structure.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&NVIC_Init_Structure);
	
	TIM_Cmd(TIM2,ENABLE);
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
