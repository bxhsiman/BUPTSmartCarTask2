#include "stm32f10x.h"                  // Device header

void LIGHTSENSER_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
	uint8_t LIGHTSENSER_GET(void)
	{
		
		return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
	}
