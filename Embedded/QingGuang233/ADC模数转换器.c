#include "stm32f10x.h" 				// Device header
#include "Delay.h"
#include "OLED.h"
#define bool char
#define true 1
#define false 0

int main(void){
	
	OLED_Init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	
	OLED_ShowString(1,1,"result:");
	OLED_ShowString(2,1,"voltage:");
	OLED_ShowString(2,10,".");
	while(1){
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
		while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
		int result = ADC_GetConversionValue(ADC1);
		float voltage = (float)result / 4095 * 3.3;
		OLED_ShowNum(1,8,result,4);
		OLED_ShowNum(2,9,voltage,1);
		OLED_ShowNum(2,11,((int)(voltage*100))%100,2);
	}
	
}
