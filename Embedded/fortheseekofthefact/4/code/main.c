/*------------------------------------------------------
HOMEWORK4
--------------------------------------------------------*/

#include "include_all.h"

/* 中断优先级组 */
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
    
    BOARD_ConfigMPU();            /* 初始化内存保护单元 */
    
    BOARD_BootClockRUN();         /* 初始化开发板时钟   */ 
    
	POWER_ENABLE();               /* 开启母板外围电路电源 与母版设计有关 */

    BOARD_InitPins();             /* 串口管脚初始化     */
    BOARD_InitDebugConsole();     /* 初始化串口         */

    NVIC_SetPriorityGrouping(NVIC_Group2);

	Test_ADC(); //TEST_ADC.C
    while (1)
    {     

    }
}
