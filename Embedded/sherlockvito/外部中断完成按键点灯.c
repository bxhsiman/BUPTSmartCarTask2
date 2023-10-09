// 外部中断完成按键点灯  按键连接到PB11  点灯连接到PA1  使用stm32f103c8t6开发板

#include "stm32f10x.h"                  // Device header


void Key_Init(void)         //按键初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);        //使能GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);         //使能AFIO时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;    //定义GPIO结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);   //初始化GPIOB
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11); //AFIO配置
	
	EXTI_InitTypeDef EXTI_InitStructure;    //定义EXTI结构体
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
	EXTI_Init(&EXTI_InitStructure);         //初始化EXTI
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //选择优先级分组
	
	NVIC_InitTypeDef NVIC_InitStructure;    //定义NVIC结构体
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);        //初始化NVIC
}

void LED_Init(void)       //LED初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //使能GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;    //定义GPIO结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化GPIOA
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1);    //初始化为高电平，灯灭
}

void LED_Turn(void)         //LED翻转
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0) 
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);    
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
}


int main(void)
{

	Key_Init();
	LED_Init();

	while(1)
	{
            
	}
}

void EXTI15_10_IRQHandler(void)  //中断函数
{
	if(EXTI_GetITStatus(EXTI_Line11) == SET)    //判断是否产生中断
	{
		LED_Turn(); 
		EXTI_ClearITPendingBit(EXTI_Line11);  //清除中断标志位
	}
}