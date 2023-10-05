#include "stm32f10x.h"                  // Device header
void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//打开ADC和PA0时钟
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//adc时钟分频，不超频的话只能选6或8
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;//模拟输入模式
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//初始化PA0口作为接收模拟输入
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	//将adc输入端口与转换列表建立映射，这里把端口0与列表第一个位置建立映射
	//同时设置采样时间
	
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;//连续转换，关闭
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;//右对齐
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//外部触发关闭，这里用软件
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;//只用一个转换器，独立模式
	ADC_InitStruct.ADC_NbrOfChannel=1;//只有一个端口
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;//扫描转换，关闭
	ADC_Init(ADC1,&ADC_InitStruct);//初始化ADC
	
	ADC_Cmd(ADC1,ENABLE);//ADC通电
	
	ADC_ResetCalibration(ADC1);//校准ADC，先复位
	while(ADC_GetResetCalibrationStatus(ADC1)==SET);//等待直到复位完成
	ADC_StartCalibration(ADC1);//校准
	while(ADC_GetCalibrationStatus(ADC1)==SET);//等待直到校准完成，校准能提高精度
}

uint16_t AD_Getval(void)
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件触发转换
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);//等到转换完成
	return ADC_GetConversionValue(ADC1);//读取结果
	//读取后ADC会自动清除标志位，不用修改标志位了
}
