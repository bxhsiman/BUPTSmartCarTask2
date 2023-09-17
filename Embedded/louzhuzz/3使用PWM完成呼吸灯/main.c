#include <STC89C5xRC.H>
#include <Timer0.h>

unsigned char Counter,Compare,T;
sbit LED = P2^0;

void main()
{
	Compare=1;
	T=1;
	Timer0_Init();
	while(1)
	{
		
	}
}


void Timer0_Routine() interrupt 1
{
		TL0 = 0xA4;		
		TH0 = 0xFF;		
		Counter++;
		if(Counter>=100){
			Counter = 0;
			if(T%2==1)
				Compare++;
			else
				Compare--;
			if(Compare==100||Compare==0){
				T++;
			}
		}
		if(Counter < Compare)
		{	
			LED = 0;
		}
		else
		{
			LED = 1;
		}
}