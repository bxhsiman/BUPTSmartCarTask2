#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void KEY_Init (void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_11);
	
}

uint8_t KEY_Getnum (void)
{
	
	uint8_t Keynum = 0;
	if( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0 )
	{
		
		Delay_ms(20);
		while ( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0 )
		Delay_ms(20);
		Keynum = 1;
	}
	if( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0 )
	{
		
		Delay_ms(20);
		while ( GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0 )
		Delay_ms(20);
		Keynum = 2;
	}
	
	return Keynum;

}
