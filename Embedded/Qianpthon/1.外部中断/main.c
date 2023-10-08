#include <REGX52.H>
sbit LED=P2^0;
void main()
{
	IT0=1;
	IE0=0;
	EX0=1;
	EA=1;
	PX0=1;
	while(1)
	{
		
	}
}
void Int0_Rountine(void) interrupt 0
{
	LED=~LED;
}