#include "reg52.h"
typedef unsigned int u16;
typedef unsigned char u8;
sbit led1=P2^0;
void time0_init(void)
{
	TMOD|=0x01;
	TH0=0XFC;
	TL0=0X18;
	ET0=1;
	EA=1;
	TR0=1;
}
void main()
{
	time0_init();
	while(1)
	{
	}
}
void time0() interrupt 1
{
	static u16 i;
	TH0=0XFC;
	TL0=0X18;
	i++;
	if(i==1000)
	{
		i=0;
		led1=!led1;
	}
}