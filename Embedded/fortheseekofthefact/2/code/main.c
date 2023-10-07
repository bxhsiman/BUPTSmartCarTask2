/*------------------------------------------------------
homework two
--------------------------------------------------------*/

#include "include_all.h"

/* 中断优先级组 */
#define NVIC_Group0   0x07
#define NVIC_Group1   0x06
#define NVIC_Group2   0x05
#define NVIC_Group3   0x04
#define NVIC_Group4   0x03


/*bujingqueyanshi*/
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
    delayms(200);
}
 
int main(void)
{  
    
    BOARD_ConfigMPU();
    BOARD_BootClockRUN();
    POWER_ENABLE();
    BOARD_InitPins();
    BOARD_InitDebugConsole();
    NVIC_SetPriorityGrouping(NVIC_Group2);
    Test_PIT();
    while (1)
    {     

    }
}
