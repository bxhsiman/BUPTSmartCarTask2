#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_Init_Structure);

	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBase_Init_Structure;
	
	TIM_TimeBase_Init_Structure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBase_Init_Structure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBase_Init_Structure.TIM_Period = 100 - 1;     //ARR
	TIM_TimeBase_Init_Structure.TIM_Prescaler = 720 - 1;     //PSC
	TIM_TimeBase_Init_Structure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBase_Init_Structure);
	
	TIM_OCInitTypeDef TIM_OC_Init_Structure;
	
	TIM_OCStructInit(&TIM_OC_Init_Structure);
	
	TIM_OC_Init_Structure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_Init_Structure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC_Init_Structure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_Init_Structure.TIM_Pulse = 0;    //CCR
	
	TIM_OC1Init(TIM2,&TIM_OC_Init_Structure);
	
	TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);
}

void PWM_SetPrescaler(uint16_t Prescaler)
{
	TIM_PrescalerConfig(TIM2,Prescaler,TIM_PSCReloadMode_Immediate);
}	



