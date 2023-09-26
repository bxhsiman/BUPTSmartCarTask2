#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "XPT2046.h"

unsigned int ADValue;

void Delay(unsigned int xms)
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

void main(void)
{
	LCD_Init();
	LCD_ShowString(1,1,"ADJ  NTC  GR");
	while(1)
	{
		ADValue=XPT2046_ReadAD(XPT2046_XP);		//可调电阻
		LCD_ShowNum(2,1,ADValue,3);				
		ADValue=XPT2046_ReadAD(XPT2046_YP);		//热敏电阻
		LCD_ShowNum(2,6,ADValue,3);				
		ADValue=XPT2046_ReadAD(XPT2046_VBAT);	//光敏电阻
		LCD_ShowNum(2,11,ADValue,3);			
		Delay(100);
	}
}
