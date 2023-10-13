#include "stm32f10x.h"                  // Device header

void IC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_Init_Structure);

	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBase_Init_Structure;
	
	TIM_TimeBase_Init_Structure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBase_Init_Structure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBase_Init_Structure.TIM_Period = 65536-1;     //ARR
	TIM_TimeBase_Init_Structure.TIM_Prescaler = 72-1;     //PSC
	TIM_TimeBase_Init_Structure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBase_Init_Structure);

	TIM_ICInitTypeDef TIM_IC_Init_Structure;
	TIM_IC_Init_Structure.TIM_Channel = TIM_Channel_1;
	TIM_IC_Init_Structure.TIM_ICFilter = 0xF;
	TIM_IC_Init_Structure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_IC_Init_Structure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_IC_Init_Structure.TIM_ICSelection = TIM_ICSelection_DirectTI;

	TIM_ICInit(TIM3,&TIM_IC_Init_Structure);
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3,ENABLE);
}

uint32_t IC_GetFreq(void)
{
	return 1000000/TIM_GetCapture1(TIM3);
}
