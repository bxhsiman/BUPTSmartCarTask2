//先定义一下
#define LED_GPIO_RCC    RCC_APB2Periph_GPIOA  
#define LED_GPIO_PORT   GPIOA  
#define LED_GPIO_PIN    GPIO_Pin_1

#define EXTI_RCC        RCC_APB2Periph_EXTI  
#define EXTI_PORT       EXTI  
#define EXTI_PIN        EXTI_Pin_1  

//初始化
void EXTI_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;

    // 使能 EXTI 模块  
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 配置外部中断引脚（PIN_1）为低电平触发  
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

    // 设置外部中断优先级  
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


//3. 在 main 函数中，调用外部中断初始化函数：

int main(void)
{
    EXTI_Init();

    // 使能 LED 引脚输出  
    GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);

    // 进入循环  
    while (1)
    {
        // 等待外部中断触发  
    }
}


//外部中断函数如下

void EXTI1_IRQHandler(void)
{
    // 检查是否是外部中断引脚（PIN_1）触发  
    if (EXTI_GetITStatus(EXTI_PIN) != RESET)
    {
        // 清除外部中断标志位  
        EXTI_ClearITPendingBit(EXTI_PIN);

        // 切换 LED 状态  
        GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN); // 点亮 LED  
        GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN); // 熄灭 LED  
    }
}
