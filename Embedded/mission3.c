#include "stm32f10x.h"

void PWM_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;

    // 配置 GPIOA8 为 PWM 输出  
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//这里需要复用，，使引脚控制权交给片上外设，PWM波形才能通过引脚输出
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_PWM);


    TIM_TimeBaseStruct.TIM_Prescaler = (SystemCoreClock / 1000) - 1; // 预分频,1ms时基  
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStruct.TIM_Period = 1000 - 1; // ARR 重装载值，定时器计数 1s  
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);//通道在此

    // PWM1  
    TIM_Cmd(TIM1, ENABLE);
}

void BreathingLight(uint16_t dutyCycle) {
    TIM_SetCompare1(TIM1, dutyCycle);
}

int main(void) {
    PWM_Init();
     uint16_t dutyCycle = 500; // 占空比 50%  
        BreathingLight(dutyCycle);

        dutyCycle += 10;
        if (dutyCycle > 1000) {
            dutyCycle = 500;
        }
    while (1) {
   
        BreathingLight(dutyCycle);

        // 延时一段时间，使呼吸灯效果更明显  
        for (int i = 0; i < 1000; i++) { PWM_SetCompare1(i); Delay_ms(10); };
        for (int i = 0; i < 1000; i++) { PWM_SetCompare1(100-i); Delay_ms(10); };
    }
}