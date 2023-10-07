/*------------------------------------------------------
this is the first question
--------------------------------------------------------*/

#include "include_all.h"

/* �ж����ȼ��� */
#define NVIC_Group0   0x07
#define NVIC_Group1   0x06
#define NVIC_Group2   0x05
#define NVIC_Group3   0x04
#define NVIC_Group4   0x03


/* ����ȷ��ʱ*/
void delayms(uint16_t ms)
{
	volatile uint32_t i = 0;
	while(ms--)
	{
		for (i = 0; i < 30000; ++i)
		{
			__asm("NOP"); /* delay */
		}
	}	
}


/*�������Դ*/
void POWER_ENABLE(void)
{ 
    PIN_InitConfig(C10, PIN_MODE_OUTPUT, 1);
    delayms(200);
}
 

int main(void)
{  
    BOARD_ConfigMPU(); //INIT�ڴ汣����Ԫ
    BOARD_BootClockRUN(); //INIT CLOCK
    POWER_ENABLE();//��Χ��·
    BOARD_InitPins();//�ܽ�INIT
    BOARD_InitDebugConsole();//INIT����
    NVIC_SetPriorityGrouping(NVIC_Group2);

        Test_KEY();
    while (1)
    {     
    }
}
