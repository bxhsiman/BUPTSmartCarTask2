#include "stm32f10x.h" // Device header

void Key_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // open GPIOB clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  // open AFIO clock

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // default is high
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15); // 将GPI0_Pin_15设置为外部中断的触发信号

    // configure EXTI
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line15; // 通道15
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发中断
    EXTI_Init(&EXTI_InitStruct);

    // Nested Vectored Interrupt Controller
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // set group to 2(2 bits)
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);
}

// 外部中断函数模板
// void EXTI15_10_IRQHandler(void)
// {
//     if (EXTI_GetITStatus(EXTI_Line15) == SET)
//     {
//         // do something here...
//         EXTI_ClearITPendingBit(EXTI_Line15);
//     }
// }
