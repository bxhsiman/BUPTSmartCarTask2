#include "public.h"
#include "LCD1602.h"
#include "xpt2046.h"
#include <stdio.h>
char adc_str[16];
void time0_init(void)
{
	TMOD|=0x01;
	TH0=0X00;
	TL0=0X00;
	ET0=1;
	EA=1;
	TR0=1;
}

void main()
{	
	u16 adc_value=1;
	
  time0_init();	
  LCD1602_init();	
	while(1)
	{
		
		adc_value=xpt2046_adc(0xA4);//测量光敏电阻
	  sprintf(adc_str,"%d",adc_value);
	  //strcpy(adc_str,"wrnm"); (这行是debug的大功臣！！！！)
	  
	}
}

void time0() interrupt 1
{
	LCD1602_display(adc_str);
}