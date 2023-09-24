#include <STC89C5xRC.H>

void Timer0_Init()
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
}