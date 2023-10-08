//定时器中断完成LED闪烁 点灯连接到PA1 开启TIM2时钟 使用stm32f103c8t6开发板

#include "stm32f10x.h"                  // Device header

void Timer_Init(void)  // 定义定时器初始化函数
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  // 使能TIM2时钟
	
	TIM_InternalClockConfig(TIM2);  // 配置TIM2时钟源为内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;  // 定义TimeBase结构体
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;  
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;  
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);  // 初始化TIM2定时器
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);  // 清除TIM2更新标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  // 使能TIM2更新中断													
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // 配置中断优先级分组
	
	NVIC_InitTypeDef NVIC_InitStructure;  // 定义NVIC结构体
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
	NVIC_Init(&NVIC_InitStructure);  // 初始化NVIC
	
	TIM_Cmd(TIM2, ENABLE);  // 使能TIM2定时器
}

void LED_Init(void)  // 定义LED初始化函数
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 使能GPIOA时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;  // 定义GPIO结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);  // 初始化GPIOA

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
	LED_Init();  
	Timer_Init();  
	
	while (1)  
	{
		
	}
}

void TIM2_IRQHandler(void)  // 定时中断函数
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)  
	{
		LED_Turn();		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  
	}
}