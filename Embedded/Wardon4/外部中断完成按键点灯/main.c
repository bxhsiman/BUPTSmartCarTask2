#include <REGX52.H>
#include "Delay.h"
#include "INT0AND1.h"
void main()
{
	INT1Init();
	while(1);
}

void int1() interrupt 1
{
	Delay(20);
	if(P3_3==0)//P3_3可以接收外部中断1
		P2_0 = ~P2_0;
}
