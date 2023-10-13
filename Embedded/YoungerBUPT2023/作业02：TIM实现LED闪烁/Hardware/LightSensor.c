#include "stm32f10x.h"                  // Device header

void Light_Sensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_Init_Structure);
}

uint16_t Light_Sensor_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}
