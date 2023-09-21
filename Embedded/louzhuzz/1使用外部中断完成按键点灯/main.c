#include <STC89C5xRC.H>

sbit k3=P3^2; 
sbit led=P2^0; 

void delay(unsigned int i)
{
	while(i--);
}

void Int0Init()
{
	IT0=1; // 
	EX0=1;
	EA=1;
}

void main()
{
	Int0Init();
	while(1);
}

void Int0() interrupt 0
{
	delay(1000);
	if(k3==0)
	{
		led = ~led;
	}
}