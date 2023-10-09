#include "stm32f10x.h"   // Device header
#include "led.h"
void Tim_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//打开时钟
	
	TIM_InternalClockConfig(TIM2);//选择时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//1分频，不过这个分频不重要
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//选择上升计数
	TIM_TimeBaseInitStruct.TIM_Period=10000-1;//选择最大值
	TIM_TimeBaseInitStruct.TIM_Prescaler=7200-1;//选择分频
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//打开更新终端通道
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置优先级分组
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;//选择终端线路
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;//使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//选优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM2,ENABLE);//打开时钟计数
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)//检查标志位
	{
		led1_turn();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//标志位清零，结束中断
	}
}
