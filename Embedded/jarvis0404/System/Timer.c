#include "stm32f10x.h"

void Timer_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 为定时器开启内部时钟 @72MHz

    // 将TIM2配置为RCC内部时钟（internal clock）
    TIM_InternalClockConfig(TIM2); // default is internal clock for peripheral

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;     // 设置滤波采样分频率
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseInitStruct.TIM_Period = 10000 - 1;               // 重装值
    TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;             // 预分频值
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;            // advanced-control timer需配置
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    // Time Base init之后，TIM_Cmd之前，将标志位清除，消除reset后进入一次中断
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 中断输出控制：update interrupt（更新中断）

    // 配置NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;           // 选择NVIC通道
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;           // 使能通道
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2; // 抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;        // 响应优先级
    NVIC_Init(&NVIC_InitStruct);

    TIM_Cmd(TIM2, ENABLE); // timer 运行控制（开始计时）
}

/* Timer2 中断函数模板
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
*/
