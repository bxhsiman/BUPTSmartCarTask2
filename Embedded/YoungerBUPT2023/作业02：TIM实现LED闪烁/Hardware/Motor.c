#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Structure;
	GPIO_Init_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init_Structure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_Init_Structure);
	
	PWM_Init();
}

void Montor_SetSpeed(int16_t Speed)
{
	if(Speed>=0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		PWM_SetCompare(Speed);
	}
	else if(Speed<0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		Speed = -Speed;
		PWM_SetCompare(Speed);
	}
}






