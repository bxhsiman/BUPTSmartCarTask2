
#include "stm32f10x.h"


void TIM3_Init(void) {
    // �õ��Ƕ�ʱ��3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    // ��ʼ������
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 500 - 1;  // ��������Ϊ500
    TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;  // Ԥ��Ƶ��Ϊ7200
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // ���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  // ʱ�ӷ�Ƶ����Ϊ1
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;  // �ظ�����ֵΪ0
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    // ��ʹ�ܶ�ʱ�������¼�
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM3, ENABLE);
}
//�жϴ���
void TIM3_IRQHandler(void) {
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
        // �����ʱ��3�ĸ����жϱ�־λ
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

        // ����LED����״̬��ת
        GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1)));
    }
}

int main(void) {  // ��ʼ����ʱ��3
    TIM3_Init();
    // ʹ��GPIOB��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // ����LED����Ϊ�������
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

  
}