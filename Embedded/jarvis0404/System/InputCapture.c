#include "stm32f10x.h" // Device header

// @ 1MHz 频率测量
void IC_Init(void)
{
    // open internal clock at APB2 BUS for TIM2 Periphral
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 配置GPIO端口为输入端口
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // GPIO 配置为上拉输入
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;     // PA6 对应TIM3_CH1
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    TIM_InternalClockConfig(TIM3); // 使用片内时钟

    // 配置时基单元（Time Base）
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;     // 滤波采样分频率
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseInitStruct.TIM_Period = 65535 - 1;               // 重装值（ARR:Auto Reload Register）
    TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;               // 预分频值，设置测量频率
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;            // 高级定时器配置用
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

    TIM_ICInitTypeDef TIM_ICInitStruct;
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;                // 输入通道为Channel 1
    TIM_ICInitStruct.TIM_ICFilter = 0xF;                         // 采样滤波频率，不影响测量频率
    TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;     // 上升沿触发
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;           // 输入prescaler配置
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI; // 直连该通道
    TIM_ICInit(TIM3, &TIM_ICInitStruct);
    TIM_PWMIConfig(TIM3, &TIM_ICInitStruct);

    // 将通道配置为从模式触发
    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);    // Filtered Timer Input 1作为从触发输入
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset); // 检测到rising时，CNT由硬件清零

    TIM_Cmd(TIM3, ENABLE); // timer 运行控制（开始计时）
}

// 测量外部输入周期已计算其频率
uint32_t IC_GetFreq(void)
{
    // 读取CCR（Compare/Capture Register）寄存器计数值
    return 1000000 / (TIM_GetCapture1(TIM3) + 1); // +1 手动+-1调整误差
}

uint8_t IC_GetDuty(void)
{
    return (TIM_GetCapture2(TIM3) + 1) * 100 / (TIM_GetCapture1(TIM3) + 1);
}
