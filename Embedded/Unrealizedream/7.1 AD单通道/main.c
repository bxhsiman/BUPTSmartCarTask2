#include "stm32f10x.h"
#include "oled.h"
#include "delay.h"
#include "ad.h"

uint16_t ADVALUE;
float VOLTAGE ;

int main(void)
{
	OLED_Init();
	AD_Init();
	
	
	OLED_ShowString(1,1,"Advalue:");
	OLED_ShowString(2,1,"Voltage:0.00V");
	while(1)
	{
		ADVALUE =  AD_GETVALUE();
		VOLTAGE = (float)ADVALUE / 4095 *3.3 ;
		
		OLED_ShowNum(1,9,ADVALUE,4);
		OLED_ShowNum(2,9,VOLTAGE,4);
		OLED_ShowNum(2,11,(uint16_t)(VOLTAGE * 100) % 100,2);
		
		Delay_ms(100);
	}
	
	
}






