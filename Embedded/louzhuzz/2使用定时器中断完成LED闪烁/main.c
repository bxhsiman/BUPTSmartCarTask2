#include <STC89C5xRC.H>
#include <Timer0.h>

/*void Timer0_Init()
{
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL0 = 0x66;		
	TH0 = 0xFC;		
	TF0 = 0;		
	TR0 = 1;		
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}*/


void main()
{
	Timer0_Init();
	while(1)
	{
		
	}
}

unsigned int T0Count;
void Timer0_Routine() interrupt 1
{
	TL0 = 0x66;		
	TH0 = 0xFC;
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count = 0;
		P20 = ~P20;
	}
}