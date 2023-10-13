#include "stm32f10x.h"                  // Device header
#include "OLED.h"

int16_t Encoder_Count = 0;

void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);    //配置了GPIO，AFIO的时钟
	//EXTI和NVIC的时钟都是打开的，所以不用打开
	
	GPIO_InitTypeDef GPIO_Init_Structure;   //初始化GPIO
	
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Init_Structure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	EXTI_InitTypeDef ECTI_Init_Structure;    //初始化EXTI
	
	ECTI_Init_Structure.EXTI_Line = EXTI_Line0 | EXTI_Line1;
	ECTI_Init_Structure.EXTI_LineCmd = ENABLE;
	ECTI_Init_Structure.EXTI_Mode = EXTI_Mode_Interrupt;
	ECTI_Init_Structure.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_Init(&ECTI_Init_Structure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //初始化NVIC

	NVIC_InitTypeDef NVIC_Init_Structure1;
	NVIC_Init_Structure1.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_Init_Structure1.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init_Structure1.NVIC_IRQChannelPreemptionPriority = 1;   //根据表格更改
	NVIC_Init_Structure1.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_Init_Structure1);
	
	NVIC_InitTypeDef NVIC_Init_Structure2;
	NVIC_Init_Structure2.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_Init_Structure2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init_Structure2.NVIC_IRQChannelPreemptionPriority = 1;   //根据表格更改
	NVIC_Init_Structure2.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_Init_Structure2);
}

int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp = Encoder_Count;
	Encoder_Count = 0;
	return Temp;
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
		{
			Encoder_Count--;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
		
	}
}

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
		{
			Encoder_Count++;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}








