#include "stm32f10x.h"                  // Device header
#include "OLED.h"

void Sensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_Init_Structure);
	
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_Init_Structure);
}

int16_t GetWay(void)
{
	if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==1 
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
	||
		(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==1 
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==1
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0))
	{
		return -1;
	}
	if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0 
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==1
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)
	|| (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==1 
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==1
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1
	))
	{
		return 0;
	}
	if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1)
	||
		(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==1
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1))
	{
		return 1;
	}
	if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0
		&& GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0))
	{
		return 100;
	}
}





