#include "stm32f10x.h"                  // Device header
void led_init(void)//初始化led输出端口
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;//A1和A2两个端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2);
}

void led1_turn(void)//A1上的led状态反转
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)//目前是0，设为1
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	else//目前是1，设为0
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
}

void led2_turn(void)//反转A2上的led
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
}

void led1_on(void)//设为0，打开led
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}

void led1_off(void)//设为1，关闭led
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

void led2_on(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

void led2_off(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}
