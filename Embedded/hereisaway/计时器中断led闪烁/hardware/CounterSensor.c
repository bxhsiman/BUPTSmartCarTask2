#include "stm32f10x.h"                  // Device header

uint16_t Sensor_Count;

void CounterSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//GPIO和AFIO时钟使能
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//初始化GPIO
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	//初始化AFIO，B14号口
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line14;//使用14号线
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;//允许中断
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//中断模式
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//中断标志，出现下降
	EXTI_Init(&EXTI_InitStructure);//初始化EXTI
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//两种优先级的个数，都给2位，各4个
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
	//使用10-15号口共用的端口输出
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//开启
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	//优先级范围都为0-3，都设成1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);//初始化NVIC
}

uint16_t Get_Sensor_Count(void)
{
	return Sensor_Count;//返回计数结果
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line14)==SET)//检测是不是14号线的中断
	{
		Sensor_Count++;//计数
		EXTI_ClearITPendingBit(EXTI_Line14);//结束这次中断
	}
}
