#include "stm32f10x.h" // Device header

// @ 1KHz
void PWM_Init(void)
{
    // open internal clock at APB2 BUS for TIM2 Periphral
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // GPIO 配置为复用推挽输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;       // PA6 对应TIM3_CH1
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    TIM_InternalClockConfig(TIM3); // 使用片内时钟

    // 配置时基单元（Time Base）
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;     // 滤波采样分频率
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;                 // 重装值
    TIM_TimeBaseInitStruct.TIM_Prescaler = 720 - 1;              // 预分频值
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;            // 高级定时器配置用
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

    // OC: Output Compare
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct);                   // 给结构体变量赋初值
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;         // PWM1 模式
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; // active输出高电平
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 10; // 设置默认compare1值
    TIM_OC1Init(TIM3, &TIM_OCInitStruct);

    TIM_Cmd(TIM3, ENABLE); // timer 运行控制（开始计时）
}

void PWM_SetCompare1(uint16_t cmp)
{
    TIM_SetCompare1(TIM3, cmp);
}
