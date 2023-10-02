#include <REGX52.H>

void INT0Init()
{
	IT0=1;//边沿触发方式，下降沿有效。P3_2控制
	EX0=1;//打开INT0的中断允许
	EA=1;//打开总中断
}

void INT1Init()
{
	IT1=1;//边沿触发方式，下降沿有效。P3_3控制
	EX1=1;//打开INT0的中断允许
	EA=1;//打开总中断
}