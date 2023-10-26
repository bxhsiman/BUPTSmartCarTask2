#include <REGX52.H>
#include "LCD1602.h"   
#include "Delay.h"     
#include "XPT2046.h"

unsigned int ADValue;

void main()
{
	LCD_Init();

	LCD_ShowString(1,1,"ADJ NTC RG");

	while(1)
	{
		ADValue=XPT2046_ReadAD(XPT2046_XP_8);  //电位器
		Delay(10);
		LCD_ShowNum(2,1,ADValue,3);
		
		ADValue=XPT2046_ReadAD(XPT2046_YP_8);  //热敏
		Delay(10);
		LCD_ShowNum(2,5,ADValue,3);		       
		
		ADValue=XPT2046_ReadAD(XPT2046_VBAT_8);//光敏
		Delay(10);
		LCD_ShowNum(2,9,ADValue,3);
	}
}

//	LCD_ShowChar(1,1,0x41);
//	LCD_ShowNum(1,9,66,2);
//	LCD_ShowSignedNum(1,12,-88,2);
//	LCD_ShowHexNum(2,1,0xA5,2);
//	LCD_ShowBinNum(2,4,0xA5,8);
//	LCD_ShowChar(2,13,0xDF);
//	LCD_ShowChar(2,14,'C');
//	LCD_ShowString(1,16,"Welcome to China!");