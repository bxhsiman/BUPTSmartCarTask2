//ADC获取模拟量 选择ADC获取PA0模拟量 使用stm32f103c8t6开发板                     
#include "stm32f10x.h"                  // Device header
#include "OLED.h"

void AD_Init(void)                      //ADC初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);   //时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);               //ADC 6分频
	
	GPIO_InitTypeDef GPIO_InitStructure;          //GPIO结构体          
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);          //初始化GPIO
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);        //ADC通道配置

	ADC_InitTypeDef ADC_InitStructure;          //ADC结构体
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1,&ADC_InitStructure);          //初始化ADC
	
	ADC_Cmd(ADC1,ENABLE);                 //使能ADC
    
	ADC_ResetCalibration(ADC1);                //ADC校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t AD_GetValue(void)              //获取ADC值
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}



int main(void)
{
	uint16_t ADValue;
	
	OLED_Init();    //OLED初始化
	AD_Init();      //ADC初始化

	OLED_ShowString(1,1,"ADValue:");
	
	while(1)
	{
		ADValue = AD_GetValue();
		
		OLED_ShowNum(1,9,ADValue,4);    //OLED显示AD值
	}
}
