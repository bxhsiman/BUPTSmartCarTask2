#include "stm32f10x.h"                  // Device header

void PC13_LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&GPIO_Init_Structure);
}

void PC13_LED_OFF(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
}

void PC13_LED_ON(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}




