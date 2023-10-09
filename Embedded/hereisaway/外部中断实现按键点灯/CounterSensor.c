#include "stm32f10x.h"   // Device header
#include "led.h"

void CounterSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//GPIO和AFIO时钟使能
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//读取B11口的按键
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//初始化GPIO
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);
	//初始化AFIO，B11号口
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line11;//使用11号线
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;//允许中断
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//中断模式
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//中断标志，出现下降
	EXTI_Init(&EXTI_InitStructure);//初始化EXTI
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//两种优先级的个数，都给2位，各4个
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
	//使用10-15共用的端口
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//开启
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	//优先级范围都为0-3，都设成1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);//初始化NVIC
}


void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line11)==SET)//检测是不是11号线的中断
	{
		led1_turn();
		EXTI_ClearITPendingBit(EXTI_Line11);//结束这次中断
	}
}
