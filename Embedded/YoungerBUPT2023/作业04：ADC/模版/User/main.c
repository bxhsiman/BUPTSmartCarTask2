#include "stm32f10x.h"                  // Device header
#include "AD.h"
#include "OLED.h"

uint16_t ADValue;

int main()
{
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1,1,"AD:");
	
	while(1)
	{
		ADValue=AD_GetValue();
		
		OLED_ShowNum(1,4,ADValue,4); 
	}
}
