#include <REGX52.H>

void Delay20ms(void)	//@11.0592MHz
{
	unsigned char data i, j;

	i = 216;
	j = 37;
	do
	{
		while (--j);
	} while (--i);
}

void main()
{
	EA=1;//打开总中断开关
	EX0=1;//打开外部中断0
	IT0=1;//设置外部中断的触发方式
	while(1);
}

void int0() interrupt 0
{
	Delay20ms();
	if(P3_2==0)
		P2_0 = ~P2_0;
}
