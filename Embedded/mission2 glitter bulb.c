
#include "stm32f10x.h"


void TIM3_Init(void) {
    // 用的是定时器3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    // 初始化内容
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 500 - 1;  // 计数周期为500
    TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;  // 预分频器为7200
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // 向上计数模式
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // 时钟分频因子为1
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;  // 重复计数值为0
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    // 让使能定时器更新事件
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM3, ENABLE);
}
//中断处理
void TIM3_IRQHandler(void) {
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        // 清除定时器3的更新中断标志位
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

        // 控制LED引脚状态翻转
        GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1)));
    }
}

int main(void) {  // 初始化定时器3
    TIM3_Init();
    // 使能GPIOB的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 配置LED引脚为推挽输出
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

  
}