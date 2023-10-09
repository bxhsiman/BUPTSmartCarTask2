#include "stm32f10x.h"  // Device header
#include "Delay.h"
void key_init(void)//按键端口初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//设置为读取模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_11;//用B0和B11端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
uint8_t get_keynum(void)
{
	uint8_t keynum=0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)//B0读到0，也就是按下
	{
		Delay_ms(20);//先跳过按下后的震动
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0);//再跳过按下后的稳定状态
		Delay_ms(20);//再跳过松开后的震动
		keynum=1;//1表示按下的是B0的开关
	}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)//B11口的开关类似
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);
		Delay_ms(20);
		keynum=2;
	}
	return keynum;//返回开关数据
}



	