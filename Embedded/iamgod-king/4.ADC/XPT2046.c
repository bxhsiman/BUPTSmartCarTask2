#include <REGX52.H>
#include "Delay.h"
sbit XPT2046_CS=P3^5;
sbit XPT2046_DCLK=P3^6;
sbit XPT2046_DIN=P3^4;
sbit XPT2046_DOUT=P3^7;

unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned char i;
	unsigned int ADValue=0;
	XPT2046_CS=0;
	XPT2046_DCLK=0;
	
	for(i=0;i<8;i++)
	{
		XPT2046_DIN=Command&(0x80>>i);      //不太明白这个>>
		XPT2046_DCLK=1;
		Delay(10);
		XPT2046_DCLK=0;
	}
	for(i=0;i<16;i++)
	{
		XPT2046_DCLK=1;
		Delay(10);
		XPT2046_DCLK=0;
		if(XPT2046_DOUT){ADValue|=(0x8000>>i);}//还有这个
	}
	
	XPT2046_CS=1;
	return ADValue>>8;
//至此显示0000，不赋值是2480
	/*
	if(Command&0x08)
	{
		return ADValue>>8;                     //读取从前还是从后？
	}
	else
	{
		return ADValue>>4;
	}
	*///NIMA根本不显示啊
}