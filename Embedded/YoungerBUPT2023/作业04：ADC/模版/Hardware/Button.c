#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Button_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_Init_Structure);
}

uint16_t Button_Sense(void)
{
	uint16_t Sense = 0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0);
		Delay_ms(20);
		Sense = 1;
	}
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0);
		Delay_ms(20);
		Sense = 2;
	}
	
	return Sense;
	
}
