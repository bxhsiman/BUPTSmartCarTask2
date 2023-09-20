#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "AD.h"

int main(void)
{
	
	OLED_Init();
	AD_Init();
	uint16_t num;
	
	while (1)
	{
		num = AD_GetValue();
		OLED_ShowNum(1,1,num,4);
		
	}
}
