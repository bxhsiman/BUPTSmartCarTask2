/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������i.MX RT1064���İ�-���ܳ���
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2017��2��1��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR8.30.1�����ϰ汾
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "fsl_adc.h"
#include "fsl_iomuxc.h"
#include "LQ_ADC.h"



/**
  * @brief    ADCģ���ʼ��
  *
  * @param    base �� ADC1��ADC2
  * @param    CH   �� ADCͨ����
  *
  * @return   
  *
  * @note     
  *
  * @example  ADC_InitConfig(ADC1, ADC1_CH2_L14);  //��ʼ�� L14����ADC����
  *
  * @date     2019/6/10 ����һ
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
    
    /* ADC�ֱ��� 12λ */
    adcConfigStrcut.resolution=kADC_Resolution12Bit;  
    
    ADC_Init(base, &adcConfigStrcut);                              
    
    /* Ӳ��ƽ�� */
    ADC_SetHardwareAverageConfig(base, kADC_HardwareAverageCount32);
    
    /* Ӳ��У׼ */
    ADC_DoAutoCalibration(base);                                    
    
}



/**
  * @brief    ADC��ȡͨ����ֵ
  *
  * @param    base �� ADC1��ADC2
  * @param    CH   �� ADCͨ����
  *
  * @return   
  *
  * @note     
  *
  * @example  ADC_Read(ADC1, ADC1_CH2_L14);  //��ȡ L14��ADֵ
  *
  * @date     2019/6/10 ����һ
  */
uint16_t ADC_Read(ADC_Type *base,ADCn_Ch_e CH)
{     
    adc_channel_config_t adcChannelConfigStruct;                           
    
    /* ����ͨ�� */
    adcChannelConfigStruct.channelNumber = CH;
    
    /* ��ת������ж� */
    adcChannelConfigStruct.enableInterruptOnConversionCompleted = false;  
    
    /* ��ʼ���� */
    ADC_SetChannelConfig(base, 0, &adcChannelConfigStruct);               
    
    /* �ȴ�ת����� */
    while (0U == ADC_GetChannelStatusFlags(base,0)){;}                    
    
    /* ����ת����� */
    return (ADC_GetChannelConversionValue(base,0));                     
}


/*!
  * @brief    ADC��ȡ��� ����ƽ��ֵ
  *
  * @param    
  *
  * @return   ��ζ�ȡ��ƽ��ֵ
  *
  * @note     
  *
  * @see      ADC_ReadMean(ADC1, ADC2_CH4_J14, 10);  //��ȡJ14 ʮ�η���ƽ��ֵ
  *
  * @date     2019/9/30 ����һ
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
  * @brief    ADC �ܽų�ʼ��
  *
  * @param    base �� ADC1��ADC2
  * @param    CH   �� ADCͨ����  
  *
  * @return   
  *
  * @note     �ڲ�����
  *
  * @example  
  *
  * @date     2019/7/22 ����һ
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


