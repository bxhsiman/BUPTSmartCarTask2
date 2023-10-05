#include "stm32f10x.h"                  // Device header
void lightsensor_init(void)//光敏传感器初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//对应端口的时钟使能，也就是打开
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//端口初始化，设为读取模式，13口
	
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	//初始值为1
}

uint8_t lightsensor_get(void)//读取光敏传感器数据
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
	//返回B13端口读到的数据
}

