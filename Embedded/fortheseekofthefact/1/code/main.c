/*------------------------------------------------------
this is the first question
--------------------------------------------------------*/

#include "include_all.h"

/* 中断优先级组 */
#define NVIC_Group0   0x07
#define NVIC_Group1   0x06
#define NVIC_Group2   0x05
#define NVIC_Group3   0x04
#define NVIC_Group4   0x03


/* 不精确延时*/
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


/*打开外设电源*/
void POWER_ENABLE(void)
{ 
    PIN_InitConfig(C10, PIN_MODE_OUTPUT, 1);
    delayms(200);
}
 

int main(void)
{  
    BOARD_ConfigMPU(); //INIT内存保护单元
    BOARD_BootClockRUN(); //INIT CLOCK
    POWER_ENABLE();//外围电路
    BOARD_InitPins();//管脚INIT
    BOARD_InitDebugConsole();//INIT串口
    NVIC_SetPriorityGrouping(NVIC_Group2);

        Test_KEY();
    while (1)
    {     
    }
}
