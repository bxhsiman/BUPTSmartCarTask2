#include "TEST_PIT.h"
#include "LQ_GPIO_Cfg.h"
#include "LQ_PIT.h"
#include "LQ_LED.h"

/*测试PIT用  volatile易变的，在中断里面会改变的变量定义时最好加上，告诉编译器不要优化，每次读取都从该变量的地址读取*/
volatile uint16_t pitIsrCnt0 = 0;   
volatile uint16_t pitIsrCnt1 = 0;
volatile uint16_t pitIsrCnt2 = 0; 

void Test_PIT(void)
{ 
    LED_Init();                             //初始化LED
    
    PIT_InitConfig(kPIT_Chnl_0, 1000UL);       //1 000us 一次中断
    PIT_InitConfig(kPIT_Chnl_1, 5000UL);       //5 000us 一次中断
    PIT_InitConfig(kPIT_Chnl_2, 1000000UL);    //1000 000us 一次中断
    
    while (true)
    {
        if (pitIsrCnt0)
        {
            PT2_22 = !PT2_22;             //翻转 C12         
            pitIsrCnt0 = 0;
        }
        if (pitIsrCnt1)
        {
            PT1_4 = !PT1_4;               //翻转 F11   
            pitIsrCnt1=0;
        }
        if (pitIsrCnt2)
        {
            LED_ColorReverse(red); 
            pitIsrCnt2=0;
        }
    }
}


