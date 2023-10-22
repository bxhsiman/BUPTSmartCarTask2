#include "stm32f10x.h"  
#include "stm32f10x_rcc.h"  
#include "stm32f10x_gpio.h"  
#include "stm32f10x_adc.h"  
#include "stm32f10x_lcd.h"

    void ADC_Config(void);
    void LCD_Config(void);

    int main(void)
    {
        ADC_Config();
        LCD_Config();

        while (1)
        {
            // 读取 ADC 数据  
            uint32_t adcValue = ADC_Read();

            // 打印 ADC 数据到 LCD 屏幕  
            LCD_Print("ADC Value: %d", adcValue);
        }
    }

    void ADC_Init(void)
    {
        // 配置 ADC  
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
        ADC_InitTypeDef ADC_InitStructure;
        ADC_InitStructure.ADC_Mode = ADC_Mode_ScanConv;
        ADC_InitStructure.ADC_ScanConvMode = ADC_ScanConvMode_Upward;
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
        ADC_InitStructure.ADC_DiscontinuousConvMode = DISABLE;
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
        ADC_InitStructure.ADC_NbrOfConversion = 1;
        ADC_Init(ADC1, &ADC_InitStructure);

        // 配置 ADC 引脚  
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        // 使能 ADC  
        ADC_Cmd(ADC1, ENABLE);
    }

    void LCD_Config(void)
    {
        // 配置 LCD 引脚  
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        // 配置 LCD  
        LCD_Init();
        LCD_SetBacklight(ENABLE);
        LCD_Clear();
    }

    uint32_t ADC_Read(void)
    {
        // 等待 ADC 转换完成  
        while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

        // 读取 ADC 值  
        uint32_t adcValue = ADC_GetConversionValue(ADC1);

        return adcValue;
    }