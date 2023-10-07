#ifndef __LQ_ADC_H__
#define __LQ_ADC_H__ 
/* //ADC资源序号与对应的管脚，      管脚名称      BGA管脚编号
ADC1_IN0  Analog channel 1 input0   GPIO_AD_B1_11   J13
ADC1_IN1  Analog channel 1 input1   GPIO_AD_B0_12   K14 
ADC1_IN2  Analog channel 1 input2   GPIO_AD_B0_13   L14
ADC1_IN3  Analog channel 1 input3   GPIO_AD_B0_14   H14
ADC1_IN4  Analog channel 1 input4   GPIO_AD_B0_15   L10
ADC1_IN5  Analog channel 1 input5   GPIO_AD_B1_00   J11
ADC1_IN6  Analog channel 1 input6   GPIO_AD_B1_01   K11
ADC1_IN7  Analog channel 1 input7   GPIO_AD_B1_02   L11
ADC1_IN8  Analog channel 1 input8   GPIO_AD_B1_03   M12
ADC1_IN9  Analog channel 1 input9   GPIO_AD_B1_04   L12
ADC1_IN10 Analog channel 1 input10  GPIO_AD_B1_05   K12
ADC1_IN11 Analog channel 1 input11  GPIO_AD_B1_06   J12
ADC1_IN12 Analog channel 1 input12  GPIO_AD_B1_07   K10
ADC1_IN13 Analog channel 1 input13  GPIO_AD_B1_08   H13
ADC1_IN14 Analog channel 1 input14  GPIO_AD_B1_09   M13
ADC1_IN15 Analog channel 1 input15  GPIO_AD_B1_10   L13

ADC2_IN0  Analog channel 2 input0   GPIO_AD_B1_11   J13
ADC2_IN1  Analog channel 2 input1   GPIO_AD_B1_12   H12
ADC2_IN2  Analog channel 2 input2   GPIO_AD_B1_13   H11
ADC2_IN3  Analog channel 2 input3   GPIO_AD_B1_14   G12
ADC2_IN4  Analog channel 2 input4   GPIO_AD_B1_15   J14
ADC2_IN5  Analog channel 1 input5   GPIO_AD_B1_00   J11
ADC2_IN6  Analog channel 1 input6   GPIO_AD_B1_01   K11
ADC2_IN7  Analog channel 1 input7   GPIO_AD_B1_02   L11
ADC2_IN8  Analog channel 1 input8   GPIO_AD_B1_03   M12
ADC2_IN9  Analog channel 1 input9   GPIO_AD_B1_04   L12
ADC2_IN10 Analog channel 1 input10  GPIO_AD_B1_05   K12
ADC2_IN11 Analog channel 1 input11  GPIO_AD_B1_06   J12
ADC2_IN12 Analog channel 1 input12  GPIO_AD_B1_07   K10
ADC2_IN13 Analog channel 1 input13  GPIO_AD_B1_08   H13
ADC2_IN14 Analog channel 1 input14  GPIO_AD_B1_09   M13
ADC2_IN15 Analog channel 1 input15  GPIO_AD_B1_10   L13
*/
typedef enum
{
  //参考手册p484 414.1.5 Modes of Operation  
  ADC1_CH0_J13=0,//         J13
  ADC1_CH1_K14=1,//         K14 
  ADC1_CH2_L14=2,//         L14
  ADC1_CH3_H14=3,//         H14
  ADC1_CH4_L10=4,//         L10
  ADC1_CH5_J11=5,//         J11
  ADC1_CH6_K11=6,//         K11
  ADC1_CH7_L11=7,//         L11
  ADC1_CH8_M12=8,//         M12
  ADC1_CH9_L12=9,//         L12
  ADC1_CH10_K12=10,//       K12
  ADC1_CH11_J12=11,//       J12
  ADC1_CH12_K10=12,//       K10
  ADC1_CH13_H13=13,//       H13
  ADC1_CH14_M13=14,//       M13
  ADC1_CH15_L13=15,//       L13
                        
  ADC2_CH0_J13=0,//         J13
  ADC2_CH1_H12=1,//         H12
  ADC2_CH2_H11=2,//         H11
  ADC2_CH3_G12=3,//         G12
  ADC2_CH4_J14=4,//         J14
  ADC2_CH5_J11=5,//         J11
  ADC2_CH6_K11=6,//         K11
  ADC2_CH7_L11=7,//         L11
  ADC2_CH8_M12=8,//         M12
  ADC2_CH9_L12=9,//         L12
  ADC2_CH10_K12=10,//       K12
  ADC2_CH11_J12=11,//       J12
  ADC2_CH12_K10=12,//       K10
  ADC2_CH13_H13=13,//       H13
  ADC2_CH14_M13=14,//       M13
  ADC2_CH15_L13=15,//       L13
  
} ADCn_Ch_e;

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
void ADC_InitConfig(ADC_Type *base, ADCn_Ch_e CH);


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
uint16_t ADC_Read(ADC_Type *base,ADCn_Ch_e CH);



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
uint16_t ADC_ReadMean(ADC_Type *base, ADCn_Ch_e CH, uint8_t count);


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
void ADC_PinInit(ADC_Type *base, ADCn_Ch_e CH);




#endif 
