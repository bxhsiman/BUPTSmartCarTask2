/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱i.MX RT1064核心板-智能车板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2017年2月1日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR8.30.1及以上版本
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "fsl_adc.h"
#include "fsl_iomuxc.h"
#include "LQ_ADC.h"



/**
  * @brief    ADC模块初始化
  *
  * @param    base ： ADC1、ADC2
  * @param    CH   ： ADC通道号
  *
  * @return   
  *
  * @note     
  *
  * @example  ADC_InitConfig(ADC1, ADC1_CH2_L14);  //初始化 L14用作ADC功能
  *
  * @date     2019/6/10 星期一
  */
void ADC_InitConfig(ADC_Type *base, ADCn_Ch_e CH)
{    
    ADC_PinInit(base, CH);
    
    adc_config_t adcConfigStrcut;   
    
    /*
    *  config->enableAsynchronousClockOutput = true;
    *  config->enableOverWrite =                 false;
    *  config->enableContinuousConversion =    false;
    *  config->enableHighSpeed =               false;
    *  config->enableLowPower =                false;
    *  config->enableLongSample =              false;
    *  config->referenceVoltageSource =        kADC_ReferenceVoltageSourceVref;
    *  config->samplePeriodMode =              kADC_SamplePeriod2or12Clocks;
    *  config->clockSource =                   kADC_ClockSourceAD;
    *  config->clockDriver =                   kADC_ClockDriver1;
    *  config->resolution =                    kADC_Resolution12Bit;
    */
    ADC_GetDefaultConfig(&adcConfigStrcut);
    
    /* ADC分辨率 12位 */
    adcConfigStrcut.resolution=kADC_Resolution12Bit;  
    
    ADC_Init(base, &adcConfigStrcut);                              
    
    /* 硬件平均 */
    ADC_SetHardwareAverageConfig(base, kADC_HardwareAverageCount32);
    
    /* 硬件校准 */
    ADC_DoAutoCalibration(base);                                    
    
}



/**
  * @brief    ADC读取通道数值
  *
  * @param    base ： ADC1、ADC2
  * @param    CH   ： ADC通道号
  *
  * @return   
  *
  * @note     
  *
  * @example  ADC_Read(ADC1, ADC1_CH2_L14);  //读取 L14的AD值
  *
  * @date     2019/6/10 星期一
  */
uint16_t ADC_Read(ADC_Type *base,ADCn_Ch_e CH)
{     
    adc_channel_config_t adcChannelConfigStruct;                           
    
    /* 传输通道 */
    adcChannelConfigStruct.channelNumber = CH;
    
    /* 关转换完成中断 */
    adcChannelConfigStruct.enableInterruptOnConversionCompleted = false;  
    
    /* 开始传输 */
    ADC_SetChannelConfig(base, 0, &adcChannelConfigStruct);               
    
    /* 等待转换完成 */
    while (0U == ADC_GetChannelStatusFlags(base,0)){;}                    
    
    /* 返回转换结果 */
    return (ADC_GetChannelConversionValue(base,0));                     
}


/*!
  * @brief    ADC读取多次 返回平均值
  *
  * @param    
  *
  * @return   多次读取的平均值
  *
  * @note     
  *
  * @see      ADC_ReadMean(ADC1, ADC2_CH4_J14, 10);  //读取J14 十次返回平均值
  *
  * @date     2019/9/30 星期一
  */
uint16_t ADC_ReadMean(ADC_Type *base, ADCn_Ch_e CH, uint8_t count)
{
    assert(count);
    
    uint32_t sum = 0;
    for(int i = 0; i < count; i++)
    {
        sum += ADC_Read(base, CH);
    }
    return sum/count;
}



/**
  * @brief    ADC 管脚初始化
  *
  * @param    base ： ADC1、ADC2
  * @param    CH   ： ADC通道号  
  *
  * @return   
  *
  * @note     内部调用
  *
  * @example  
  *
  * @date     2019/7/22 星期一
  */
void ADC_PinInit(ADC_Type *base, ADCn_Ch_e CH)
{
    CLOCK_EnableClock(kCLOCK_Iomuxc);           /* iomuxc clock (iomuxc_clk_enable): 0x03U */
    
    if(base == ADC1)
    {
        switch(CH)
        {
          case 0:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_11_GPIO1_IO27,0U);
            break;
          case 1:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_GPIO1_IO12,0U);
            break;
          case 2:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_GPIO1_IO13,0U);
            break;
          case 3:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_14_GPIO1_IO14,0U);
            break;
          case 4:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_15_GPIO1_IO15,0U);
            break;
          case 5:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_GPIO1_IO16,0U);
            break;
          case 6:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_GPIO1_IO17,0U);
            break;
          case 7:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_GPIO1_IO18,0U);
            break;
          case 8:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_GPIO1_IO19,0U);
            break;
          case 9:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_04_GPIO1_IO20,0U);
            break;
          case 10:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_05_GPIO1_IO21,0U);
            break;
          case 11:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_GPIO1_IO22,0U);
            break;
          case 12:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_GPIO1_IO23,0U);
            break;
          case 13:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_GPIO1_IO24,0U);
            break;
          case 14:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_GPIO1_IO25,0U);
            break;
          case 15:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_GPIO1_IO26,0U);
            break;
        }
    }
    else
    {
        switch(CH)
        {
          case 0:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_11_GPIO1_IO27,0U);
            break;
          case 1:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_12_GPIO1_IO28,0U);
            break;
          case 2:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_GPIO1_IO29,0U);
            break;
          case 3:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_GPIO1_IO30,0U);
            break;
          case 4:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_GPIO1_IO31,0U);
            break;
          case 5:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_GPIO1_IO16,0U);
            break;
          case 6:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_GPIO1_IO17,0U);
            break;
          case 7:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_02_GPIO1_IO18,0U);
            break;
          case 8:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_03_GPIO1_IO19,0U);
            break;
          case 9:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_04_GPIO1_IO20,0U);
            break;
          case 10:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_05_GPIO1_IO21,0U);
            break;
          case 11:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_GPIO1_IO22,0U);
            break;
          case 12:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_GPIO1_IO23,0U);
            break;
          case 13:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_08_GPIO1_IO24,0U);
            break;
          case 14:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_GPIO1_IO25,0U);
            break;
          case 15:
            IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_10_GPIO1_IO26,0U);
            break;
        }
    }

}


