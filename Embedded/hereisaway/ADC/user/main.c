#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "ADC.h"

uint16_t ADnum;
float v;

int main(void)
{
	OLED_Init();
	AD_Init();
	OLED_ShowString(1,1,"ADnum:");
	OLED_ShowString(2,1,"V:");
	OLED_ShowChar(2,8,'.');
	
	while(1)
	{
		ADnum=AD_Getval();
		v=(float)ADnum/4095*3.3;
		OLED_ShowNum(1,7,ADnum,4);
		OLED_ShowNum(2,7,v,1);
		OLED_ShowNum(2,9,(uint16_t)(v*100)%100,2);
	}
}
