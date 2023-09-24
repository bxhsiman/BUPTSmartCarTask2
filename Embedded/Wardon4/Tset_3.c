#include <REGX52.H>

unsigned char i,j,k;

void Timer0_Init(void)//100微秒@11.0592MHz定时器初始化
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TL0 = 0xA4;
	TH0 = 0xFF;
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

void Timer0_Routine() interrupt 1 //100微秒进入一次
{
	TL0 = 0xA4;
	TH0 = 0xFF;//设置定时器初始值
	i++;//每进入一次i自增
	if(i>=100)
	{
		if(j==100)
		k=~k;
		i = i%100;//i到100时自动归零
		j++;
		if(j>100) j = 0;
	}
	if(k==0)
	{
		if(i<j)
		  P2_0 = 1;//i小于j则灭，j/100的时候灭
	  else
		  P2_0 = 0;//i大于j则亮，（1-j）/100的时候亮
	}
	else
	{
		if(i>j)
		P2_0 = 1;//i小于j则灭，j/100的时候灭
	else
		P2_0 = 0;//i大于j则亮，（1-j）/100的时候亮
	}
	
}