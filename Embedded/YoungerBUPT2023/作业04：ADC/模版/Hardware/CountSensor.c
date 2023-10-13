#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count = 0;
void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);    //配置了GPIO，AFIO的时钟
	//EXTI和NVIC的时钟都是打开的，所以不用打开
	
	GPIO_InitTypeDef GPIO_Init_Structure;   //初始化GPIO
	
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_Structure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	
	EXTI_InitTypeDef ECTI_Init_Structure;    //初始化EXTI
	
	ECTI_Init_Structure.EXTI_Line = EXTI_Line14;
	ECTI_Init_Structure.EXTI_LineCmd = ENABLE;
	ECTI_Init_Structure.EXTI_Mode = EXTI_Mode_Interrupt;
	ECTI_Init_Structure.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_Init(&ECTI_Init_Structure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //初始化NVIC

	NVIC_InitTypeDef NVIC_Init_Structure;
	NVIC_Init_Structure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_Init_Structure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority = 1;   //根据表格更改
	NVIC_Init_Structure.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&NVIC_Init_Structure);
}

uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}

void EXTI15_10_IRQHandler(void)   //调用中断函数
{
	if(EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		CountSensor_Count++;
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}



