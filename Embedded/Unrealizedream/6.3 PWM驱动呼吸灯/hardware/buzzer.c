#include "stm32f10x.h"                  // Device header

void BUZZER_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void BUZZER_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12 );
}

void BUZZER_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12 );
}

void BUZZER_TURN(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_12)==0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12 );
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12 );
	}
}












