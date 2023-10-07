/*------------------------------------------------------
HOMEWORK4
--------------------------------------------------------*/

#include "include_all.h"

/* �ж����ȼ��� */
#define NVIC_Group0   0x07
#define NVIC_Group1   0x06
#define NVIC_Group2   0x05
#define NVIC_Group3   0x04
#define NVIC_Group4   0x03

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

void POWER_ENABLE(void)
{ 
    PIN_InitConfig(C10, PIN_MODE_OUTPUT, 1);
}
 
int main(void)
{  
    
    BOARD_ConfigMPU();            /* ��ʼ���ڴ汣����Ԫ */
    
    BOARD_BootClockRUN();         /* ��ʼ��������ʱ��   */ 
    
	POWER_ENABLE();               /* ����ĸ����Χ��·��Դ ��ĸ������й� */

    BOARD_InitPins();             /* ���ڹܽų�ʼ��     */
    BOARD_InitDebugConsole();     /* ��ʼ������         */

    NVIC_SetPriorityGrouping(NVIC_Group2);

	Test_ADC(); //TEST_ADC.C
    while (1)
    {     

    }
}
