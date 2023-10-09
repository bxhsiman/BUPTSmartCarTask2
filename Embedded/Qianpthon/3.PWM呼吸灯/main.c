#include <REGX52.H>
#include "Timer0.h"
unsigned char Counter,Compare;
sbit LED=P2^0;
void main()
{
	Compare=50;
	Timer0_Init();
		
	while(1)
	{
		
	}
}
void Timer0_Routine() interrupt 1
{
	
	TL0 = 0x9C;				
	TH0 = 0xFF;				
	Counter++;
	Counter%=100;
	if(Counter<Compare)
	{
		LED=0;
	}
	else
	{
		LED=1;
	}
	
}