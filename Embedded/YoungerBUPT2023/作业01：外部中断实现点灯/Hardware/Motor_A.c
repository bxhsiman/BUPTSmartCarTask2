#include "stm32f10x.h"                  // Device header

void Motor_A_PWM_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_11;    //TIM1_CH4
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_Init_Structure);
	
	TIM_InternalClockConfig(TIM1);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBase_Init;
	TIM_TimeBase_Init.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBase_Init.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBase_Init.TIM_Period = 100;
	TIM_TimeBase_Init.TIM_Prescaler = 7200;
	TIM_TimeBase_Init.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBase_Init);
	
	TIM_OCInitTypeDef TIM_OC_Init_Structure;
	
	TIM_OCStructInit(&TIM_OC_Init_Structure);
	
	TIM_OC_Init_Structure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_Init_Structure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC_Init_Structure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_Init_Structure.TIM_Pulse = 0;
	
	TIM_OC4Init(TIM1,&TIM_OC_Init_Structure);
	
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE); 
	
	TIM_Cmd(TIM1,ENABLE);
}

void Motor_AIN1_AIN2_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_Init_Structure);
}

void Motor_A_Speed(int16_t Speed)
{
	if (Speed<=0)
	{
		TIM_SetCompare4(TIM1,-Speed);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	}
	else
	{
		TIM_SetCompare4(TIM1,Speed);
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
}
