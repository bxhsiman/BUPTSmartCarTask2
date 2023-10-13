#include "stm32f10x.h"                  // Device header

void Steering_Engine_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_6;    //TIM1_CH4
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_Init_Structure);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBase_Init;
	TIM_TimeBase_Init.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBase_Init.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBase_Init.TIM_Period = 20000;
	TIM_TimeBase_Init.TIM_Prescaler = 72;
	TIM_TimeBase_Init.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBase_Init);
	
	TIM_OCInitTypeDef TIM_OC_Init_Structure;
	
	TIM_OCStructInit(&TIM_OC_Init_Structure);
	
	TIM_OC_Init_Structure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_Init_Structure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC_Init_Structure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_Init_Structure.TIM_Pulse = 0;   //500-2500  0---180
	
	TIM_OC1Init(TIM3,&TIM_OC_Init_Structure);
	
	TIM_Cmd(TIM3,ENABLE);
}

void Steering_Engine_SetAngle(int16_t Angle)  //-70-----70
{
	uint16_t Compare = 500 + (Angle+70)*2000/180;
	TIM_SetCompare1(TIM3,Compare);
}



