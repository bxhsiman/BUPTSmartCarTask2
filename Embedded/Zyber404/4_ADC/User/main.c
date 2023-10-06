#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

//采取数据手册中典型值
#define V25 1.43
#define AVG_SLOPE 0.0043

static uint16_t ADValue;
static float Voltage;
static uint16_t Temp;

int main(void)
{
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1, 1, "MCUTemp:");
	OLED_ShowString(2, 1, "Volatge:0.00V");
	
	while (1)
	{
		//获取电压并显示
		ADValue = AD_GetValue(ADC_Channel_0);
		Voltage = (float)ADValue / 4095 * 3.3;
		OLED_ShowNum(2, 9, Voltage, 1);
		OLED_ShowNum(2, 11, (uint16_t)(Voltage * 100) % 100, 2);

		//获取温度并显示
		ADValue = AD_GetValue(ADC_Channel_16);
		Voltage = (float)ADValue / 4095 * 3.3;
		Temp = (uint16_t)((V25 - Voltage) / AVG_SLOPE + 25);
		OLED_ShowNum(1, 9, Temp, 2);
		
		Delay_ms(100);
	}
}
