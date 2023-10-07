#include "TEST_PIT.h"
#include "LQ_GPIO_Cfg.h"
#include "LQ_PIT.h"
#include "LQ_LED.h"

/*����PIT��  volatile�ױ�ģ����ж������ı�ı�������ʱ��ü��ϣ����߱�������Ҫ�Ż���ÿ�ζ�ȡ���Ӹñ����ĵ�ַ��ȡ*/
volatile uint16_t pitIsrCnt0 = 0;   
volatile uint16_t pitIsrCnt1 = 0;
volatile uint16_t pitIsrCnt2 = 0; 

void Test_PIT(void)
{ 
    LED_Init();                             //��ʼ��LED
    
    PIT_InitConfig(kPIT_Chnl_0, 1000UL);       //1 000us һ���ж�
    PIT_InitConfig(kPIT_Chnl_1, 5000UL);       //5 000us һ���ж�
    PIT_InitConfig(kPIT_Chnl_2, 1000000UL);    //1000 000us һ���ж�
    
    while (true)
    {
        if (pitIsrCnt0)
        {
            PT2_22 = !PT2_22;             //��ת C12         
            pitIsrCnt0 = 0;
        }
        if (pitIsrCnt1)
        {
            PT1_4 = !PT1_4;               //��ת F11   
            pitIsrCnt1=0;
        }
        if (pitIsrCnt2)
        {
            LED_ColorReverse(red); 
            pitIsrCnt2=0;
        }
    }
}


