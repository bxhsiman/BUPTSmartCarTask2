#include "stm32f10x.h"                  // Device header
void buzzer_init(void)//蜂鸣器输出端口初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;//使用B12端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void buzzer_turn(void)//蜂鸣器状态反转
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12)==0)//如果目前输出的是0
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);//设置为1
	}
	else//如果目前为1
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);//设置为0
	}
}

void buzzer_on(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);//设为0，打开
}

void buzzer_off(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);//设为1，关闭
}

