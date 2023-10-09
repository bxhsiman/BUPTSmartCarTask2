
#include <REGX52.H>
void Timer0_Init()
{
	//定时器配置
		TMOD=0x01;//0000 0001，工作模式
		TF0=0;//计数置0
		TR0=1,//定时器on
		TH0=64535/256;//高八位
		TL0=64535%256;//低八位
	//中断配置
		ET0=1;
		EA=1;
    PT0=0;
}
void main()
{
	Timer0_Init();
	while(1)
	{
		
	}
}
unsigned int T0Count;
 void Timer0_Routine() interrupt 1
 {
		TH0=64535/256;
		TL0=64535%256;
		T0Count++;
	 if(T0Count>=1000)
	 {
		T0Count=0;
		 P2_0=~P2_0;
	 }
 }