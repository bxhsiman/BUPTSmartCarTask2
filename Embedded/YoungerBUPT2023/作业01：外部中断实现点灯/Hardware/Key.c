#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PC13_LED_Test.h"

void Key1_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_Init_Structure);
	
	EXTI_InitTypeDef EXTI_Init_Structure;
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);
	
	EXTI_Init_Structure.EXTI_Line = EXTI_Line7;
	EXTI_Init_Structure.EXTI_LineCmd = ENABLE;
	EXTI_Init_Structure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Init_Structure.EXTI_Trigger = EXTI_Trigger_Rising;
	
	EXTI_Init(&EXTI_Init_Structure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	
	NVIC_InitTypeDef NVIC_Init_Structure;
	
	NVIC_Init_Structure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Init_Structure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_Init_Structure.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&NVIC_Init_Structure);
}

void Key2_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_Init_Structure);
	
	EXTI_InitTypeDef EXTI_Init_Structure;
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource12);
	
	EXTI_Init_Structure.EXTI_Line = EXTI_Line12;
	EXTI_Init_Structure.EXTI_LineCmd = ENABLE;
	EXTI_Init_Structure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Init_Structure.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_Init(&EXTI_Init_Structure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	
	NVIC_InitTypeDef NVIC_Init_Structure;
	
	NVIC_Init_Structure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_Init_Structure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_Init_Structure.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&NVIC_Init_Structure);
}

void EXTI9_5_IRQHandler(void)
{
	Delay_ms(10);
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==1)
	{
		PC13_LED_ON();
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}

void EXTI15_10_IRQHandler(void)
{	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)==0)
	{
		Delay_ms(10);
		PC13_LED_OFF();
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
}



