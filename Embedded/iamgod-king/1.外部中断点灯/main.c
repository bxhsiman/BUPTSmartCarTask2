#include <REGX52.H>
typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;
sbit LED1=P2^0;//定义LED1管脚
sbit KEY3=P3^2;//定义独立按键K3控制脚
void Delay100ms()		//@12.000MHz
{
	unsigned char data i, j;
	i = 195;
	j = 138;
	do
	{
		while (--j);
	} while (--i);
}
void exti0_init(void)
{
	IT0=1;//跳变沿触发方式（下降沿）
	EX0=1;//打开INT0的中断允许
	EA=1;//打开总中断
}
void main()
{	
	exti0_init();//外部中断0配置

	while(1)
	{

	}
}
void exti0() interrupt 0 //外部中断0中断函数
{
	Delay100ms();//消斗
	if(KEY3==0)//再次判断K3键是否按下
		LED1=!LED1;//LED1状态翻转					
}