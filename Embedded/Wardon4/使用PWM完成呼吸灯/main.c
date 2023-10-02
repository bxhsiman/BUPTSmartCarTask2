#include <REGX52.H>

unsigned char i,j,k;

void Timer0_Init(void)//100微秒@11.0592MHz
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

void Timer0_Routine() interrupt 1 //100us进入一次
{
	TL0 = 0xA4;
	TH0 = 0xFF; //回到计数起点重新计数
	i++;        //i每100us进入一次中断自增的量，用来与j比较作为亮暗的标准
	if(i>=100)
	{
		if(j==100)//j每次增到一百表示进行完一个由暗到亮或由亮到暗的过程
			k=~k;   //k为0或1，用来作为是有暗到亮还是由亮变暗的指标
		i = i%100;
		j++;
		if(j>100) j = 0;
	}
	if(k==0)//由亮到暗
	{
		if(i<j)
		  P2_0 = 1;//i<j则灭，表示j/100时候为灭
		else
		  P2_0 = 0;//i>j则亮，表示（100-j）/100时候为亮
	}
	else//由暗到亮
	{
		if(i>j)
		  P2_0 = 1;
	  else
		  P2_0 = 0;
	}	
}