#include <REGX52.H>

/*配置定时器寄存器*/
void Timer0_Init(void)
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
void main()
{
	Timer0_Init();
	while(1)
	{
		
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x66;
	TH0 = 0xFC;
	T0Count++;
	if(T0Count>=500
	{
		T0Count=0;
		P2_0 = ~P2_0;
	}
}