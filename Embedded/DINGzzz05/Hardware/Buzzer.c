#include "stm32f10x.h"                  // Device header

void Buzzer_Init (uint16_t GPIO_Pin)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin);
	
}

void Buzzer_Set ( uint16_t GPIO_Pin, BitAction BitVal)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin, BitVal);
}
