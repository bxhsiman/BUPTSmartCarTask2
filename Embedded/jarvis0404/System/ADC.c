/*
单通道ADC采样，PA0作为Analog Input
*/
#include "stm32f10x.h"

void ADC1_Init(void)
{
    // 开启ADC1、GPIO端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 配置RCC到ADC的时钟分频（max 14MHz）

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN; // analog input mode
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;     // PA0 对应ADC1 channel 0
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 选择配置ADC1规则组（regular group）通道
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);

    ADC_InitTypeDef ADC_InitStruct;
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;                  // 单ADC mode
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;              // 数据右对齐（高位补0）
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 无外部触发源（软件触发）
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;                 // 非连续转换
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;                       // 不扫描
    ADC_InitStruct.ADC_NbrOfChannel = 1;                             // number of channel
    ADC_Init(ADC1, &ADC_InitStruct);

    ADC_Cmd(ADC1, ENABLE);

    // ADC 校准
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1) == SET)
        ; // await
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1) == SET)
        ; // await
}

uint16_t ADC1_GetValue(void)
{
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 软件触发convert
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
        ; // 等待convert完成
    return ADC_GetConversionValue(ADC1);
}
