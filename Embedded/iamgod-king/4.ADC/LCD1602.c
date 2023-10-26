#include <REGX52.H>
#include "LCD1602.h"

sbit LCD_RS=P2^6;
sbit LCD_E=P2^7;
sbit LCD_RW=P2^5;
#define LCD_DataPort P0

void LCD_Delay()
{
	unsigned char i,j;
	
	i=2;
	j=239;
	do
	{
		while(--j);
	}while(--i);
}


//准备？
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_DataPort=Command;
	LCD_E=1;
	LCD_Delay();
	LCD_E=0;
	LCD_Delay();
}



//写数据函数
void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;//数据
	LCD_RW=0;//写入
	LCD_DataPort=Data;
	LCD_E=1;//允许
	LCD_Delay();
	LCD_E=0;
	LCD_Delay();
}


//初始化
void LCD_Init()     
{
	LCD_WriteCommand(0x38);  //8位数据接口，2行显示，5*7点阵
	LCD_WriteCommand(0x0C);  //显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);  //数据读写操作后，光标自动加1，画面不动
	LCD_WriteCommand(0x01);  //清屏
}


//简单点
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
	if(Line==1)
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else
	{
		LCD_WriteCommand(0x80|(Column-1)+0x40);  //为什么加那玩意
	}
}


//字符
void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}


//字符串
void LCD_ShowString(unsigned char Line,unsigned char Column,unsigned char *String)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}


//取位函数
int LCD_Pow(int X,int Y)
{
	unsigned char i;
	int Result=1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}


//
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Number/LCD_Pow(10,i-1)%10);
	}
}	


//输入负数
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i;
	unsigned int Number1;   //真尼玛严谨
	LCD_SetCursor(Line,Column);
	if(Number>=0)
	{
		LCD_WriteData('+');
		Number1=Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1=-Number;
	}
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Number1/LCD_Pow(10,i-1)%10);
	}
}


//显示16进制
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	unsigned char SingleNumber;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		SingleNumber=Number/LCD_Pow(16,i-1)%16;
		if(SingleNumber<10)
		{
			LCD_WriteData('0'+SingleNumber);
		}	
		else
		{
			LCD_WriteData('A'+SingleNumber-10);
		}
	}
}	


//显示2进制
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Number/LCD_Pow(2,i-1)%2);
	}
}

