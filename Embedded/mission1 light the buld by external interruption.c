//�ȶ���һ��
#define LED_GPIO_RCC    RCC_APB2Periph_GPIOA  
#define LED_GPIO_PORT   GPIOA  
#define LED_GPIO_PIN    GPIO_Pin_1

#define EXTI_RCC        RCC_APB2Periph_EXTI  
#define EXTI_PORT       EXTI  
#define EXTI_PIN        EXTI_Pin_1  

//��ʼ��
void EXTI_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;

    // ʹ�� EXTI ģ��  
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // �����ⲿ�ж����ţ�PIN_1��Ϊ�͵�ƽ����  
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);

    // �����ⲿ�ж����ȼ�  
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


//3. �� main �����У������ⲿ�жϳ�ʼ��������

int main(void)
{
    EXTI_Init();

    // ʹ�� LED �������  
    GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);

    // ����ѭ��  
    while (1)
    {
        // �ȴ��ⲿ�жϴ���  
    }
}


//�ⲿ�жϺ�������

void EXTI1_IRQHandler(void)
{
    // ����Ƿ����ⲿ�ж����ţ�PIN_1������  
    if (EXTI_GetITStatus(EXTI_PIN) != RESET)
    {
        // ����ⲿ�жϱ�־λ  
        EXTI_ClearITPendingBit(EXTI_PIN);

        // �л� LED ״̬  
        GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN); // ���� LED  
        GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN); // Ϩ�� LED  
    }
}
