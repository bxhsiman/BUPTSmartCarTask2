/*------------------------------------------------------
HOMEWORK3
有一个问题：为啥我自己眼睛看着比较流畅但是占空比低的时候录像出来的灯颤抖很明显？？？
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


	PWM_LED_TEST();
    while (1)
    {     

    }
}
