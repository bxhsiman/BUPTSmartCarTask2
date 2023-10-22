#include "stm32f10x.h"

void PWM_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;

    // ���� GPIOA8 Ϊ PWM ���  
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//������Ҫ���ã���ʹ���ſ���Ȩ����Ƭ�����裬PWM���β���ͨ���������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_PWM);


    TIM_TimeBaseStruct.TIM_Prescaler = (SystemCoreClock / 1000) - 1; // Ԥ��Ƶ,1msʱ��  
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStruct.TIM_Period = 1000 - 1; // ARR ��װ��ֵ����ʱ������ 1s  
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);//ͨ���ڴ�

    // PWM1  
    TIM_Cmd(TIM1, ENABLE);
}

void BreathingLight(uint16_t dutyCycle) {
    TIM_SetCompare1(TIM1, dutyCycle);
}

int main(void) {
    PWM_Init();
     uint16_t dutyCycle = 500; // ռ�ձ� 50%  
        BreathingLight(dutyCycle);

        dutyCycle += 10;
        if (dutyCycle > 1000) {
            dutyCycle = 500;
        }
    while (1) {
   
        BreathingLight(dutyCycle);

        // ��ʱһ��ʱ�䣬ʹ������Ч��������  
        for (int i = 0; i < 1000; i++) { PWM_SetCompare1(i); Delay_ms(10); };
        for (int i = 0; i < 1000; i++) { PWM_SetCompare1(100-i); Delay_ms(10); };
    }
}