#include "reg52.h"
typedef unsigned int u16;
typedef unsigned char u8;
sbit led1=P2^0;
sbit key3=P3^2;

void exinter0_init(void)
{
	IT0=1;
	EX0=1;
	EA=1;
}
int main()
{
	exinter0_init();
	while(1)
	{
	}
}
void exinter0() interrupt 0
{
	led1=!led1;
}