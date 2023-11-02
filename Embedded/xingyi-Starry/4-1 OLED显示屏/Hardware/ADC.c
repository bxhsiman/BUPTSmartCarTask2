#include "stm32f10x.h"

void AD_Init(void)
{
    //开启外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    //配置ADC预分频器
    RCC_ADCCLKConfig(6);

    //GPIO初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //配置多路开关
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);

    //配置ADC转换器
    ADC_InitTypeDef ADC_Initstructure;
    ADC_Initstructure.ADC_ContinuousConvMode = DISABLE;
    ADC_Initstructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_Initstructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_Initstructure.ADC_Mode = ADC_Mode_Independent;
    ADC_Initstructure.ADC_NbrOfChannel = 1;
    ADC_Initstructure.ADC_ScanConvMode = DISABLE;
    ADC_Init(ADC1, &ADC_Initstructure);

    //开启ADC
    ADC_Cmd(ADC1, ENABLE);

    //校准ADC
    ADC_ResetCalibration(ADC1); //复位校准
    while (ADC_GetResetCalibrationStatus(ADC1) == SET); //等待复位完成

    ADC_StartCalibration(ADC1); //启动校准
    while (ADC_GetResetCalibrationStatus(ADC1) == SET); //等待校准完成
}

uint16_t AD_GetValue(void)
{
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); //启动转换
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); //等待转换完成
    return ADC_GetConversionValue(ADC1);
}
