#include "stm32f10x.h"
#include "LED.h"
#include "PWM.h"

//TIM3用于实现LED闪烁，TIM4用于实现PWM调频

uint8_t PWM_flag = 0;
uint8_t PWM_CCR = 0;

void Timer_Init(void)
{
//开启定时器时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

//选择定时器
    TIM_InternalClockConfig(TIM3);
    TIM_InternalClockConfig(TIM4);

//定时器初始化
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 7199;
    TIM_TimeBaseStructure.TIM_Prescaler = 9999;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 7199;
    TIM_TimeBaseStructure.TIM_Prescaler = 199;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);

//使能中断
    TIM_ClearFlag(TIM3,TIM_FLAG_Update);
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

    TIM_ClearFlag(TIM4,TIM_FLAG_Update);
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);

//NVIC优先级分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

//NVIC初始化
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);

//使能定时器
    TIM_Cmd(TIM3,ENABLE);
    TIM_Cmd(TIM4,ENABLE);
}

//LED闪烁
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		LED1_Turn();
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

//PWM呼吸灯
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
        if (PWM_CCR == 0)
        {
            PWM_flag = 0;
        }
        else if (PWM_CCR == 100)
        {
            PWM_flag = 1;
        }

        if (PWM_flag == 0)
        {
            PWM_CCR++;
        }
        else if(PWM_flag == 1)
        {
            PWM_CCR--;
        }

        PWM_SetCompare1(PWM_CCR);
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}
