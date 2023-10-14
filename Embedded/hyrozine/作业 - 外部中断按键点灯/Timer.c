#include "stm32f10x.h"      // Device header
#include "LED.h"

uint16_t flag ;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef Tim_InitStructure;
	Tim_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	Tim_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	Tim_InitStructure.TIM_Period = 100 - 1;
	Tim_InitStructure.TIM_Prescaler = 3600 - 1;
	Tim_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&Tim_InitStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,DISABLE);
}


//按键消抖
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_FLAG_Update) == SET)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) == 0)
		{
			if(flag != 1)
			{
				flag = 0;
			}
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) == 0)
			{
				flag++;
			}
			else
			{
				flag--;
			}
			if(flag == 2)
			{
				LED_Turn();
				TIM_Cmd(TIM2,DISABLE);
			}
		}		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}

}



