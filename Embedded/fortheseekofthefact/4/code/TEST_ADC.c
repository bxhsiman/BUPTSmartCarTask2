#include "include.h"
#include "fsl_adc.h"
#include "fsl_iomuxc.h"
#include "LQ_ADC.h"
#include "TEST_ADC.h"
#include "LQ_UART.h"
#include "LQ_KEY.h"
#include "LQ_LED.h"
#include "LQ_SGP18T.h"
#include "LQ_12864.h"
#include "stdio.h"

/* �����ⲿ��ʱ���� */
extern void delayms(uint16_t ms);



#ifdef TFT1_8

void Test_ADC(void)
{
    char txt[16];
      
    TFTSPI_Init(1);                 //LCD��ʼ��  0:����  1������
    TFTSPI_CLS(u16BLUE);            //����
    LED_Init();
    KEY_Init();          
    
    ADC_InitConfig(ADC2, ADC2_CH4_J14);   
    ADC_InitConfig(ADC1, ADC1_CH4_L10); 
    ADC_InitConfig(ADC1, ADC1_CH8_M12); 
    ADC_InitConfig(ADC1, ADC1_CH7_L11); 
    ADC_InitConfig(ADC2, ADC2_CH3_G12); 
    ADC_InitConfig(ADC1, ADC1_CH10_K12); 
    ADC_InitConfig(ADC2, ADC2_CH2_H11); 
    
    UART_InitConfig(LPUART8, 115200);
    TFTSPI_P8X16Str(2,0,"ADC HOMEWORK",u16RED,u16BLUE);
    UART_PutStr(LPUART8,(uint8_t *)"\r\nADC HOMEWORK");

    uint16_t batv0=(uint16_t)(ADC_Read(ADC2, ADC2_CH4_J14)*4.6);    //��ȡADCֵ J14 ��ص�ѹ * 100
    uint16_t batv1=(uint16_t)(ADC_Read(ADC1, ADC1_CH4_L10)*0.806);  //��ȡADCֵ L10
    uint16_t batv2=(uint16_t)(ADC_Read(ADC1, ADC1_CH8_M12)*0.806);  //��ȡADCֵ M12
    uint16_t batv3=(uint16_t)(ADC_Read(ADC1, ADC1_CH7_L11)*0.806);  //��ȡADCֵ L11
    uint16_t batv4=(uint16_t)(ADC_Read(ADC2, ADC2_CH3_G12)*0.806);  //��ȡADCֵ G12
    uint16_t batv5=(uint16_t)(ADC_Read(ADC1, ADC1_CH10_K12)*0.806); //��ȡADCֵ K12
    uint16_t batv6=(uint16_t)(ADC_Read(ADC2, ADC2_CH2_H11)*0.806);  //��ȡADCֵ H11
    while (1)
    {           
        //����ADCת��   ADC�Ļ�׼��ѹ��3.3V�ģ�RT1064ĸ���ϣ�J14ͨ��1K��4.7K�ķ�ѹ���������ص�ѹ ��ص�ѹ =  ��ADC_Read / 4095�� * 3.3 * ��1 + 4.7��
        batv0 = (uint16_t)(batv0*0.7 + 0.3*(uint16_t)(ADC_Read(ADC2, ADC2_CH4_J14)*4.6));//��ѹ�ɼ� 
        
        batv1 = (uint16_t)(batv1*0.7 + 0.3*ADC_Read(ADC1, ADC1_CH4_L10)*0.806);            
        batv2 = (uint16_t)(batv2*0.7 + 0.3*ADC_Read(ADC1, ADC1_CH8_M12)*0.806);            
        batv3 = (uint16_t)(batv3*0.7 + 0.3*ADC_Read(ADC1, ADC1_CH7_L11)*0.806);            
        batv4 = (uint16_t)(batv4*0.7 + 0.3*ADC_Read(ADC2, ADC2_CH3_G12)*0.806);            
        batv5 = (uint16_t)(batv5*0.7 + 0.3*ADC_Read(ADC1, ADC1_CH10_K12)*0.806);            
        batv6 = (uint16_t)(batv6*0.7 + 0.3*ADC_Read(ADC2, ADC2_CH2_H11)*0.806);   
        
        UART_PutStr(LPUART8,(uint8_t *)"\r\n-----------------------------\n");
        sprintf(txt,"BAT:%3.2fV ",batv0/1000.0f);
        UART_PutStr(LPUART8, (uint8_t *)txt);
        TFTSPI_P8X16Str(3,1,txt,u16RED,u16BLUE);
                                  
        sprintf(txt,"L10:%3.2fV ",batv1/1000.0f);
        UART_PutStr(LPUART8, (uint8_t *)txt);
        TFTSPI_P8X16Str(3,2,txt,u16RED,u16BLUE);
        
        sprintf(txt,"M12:%3.2fV ",batv2/1000.0f);
        UART_PutStr(LPUART8, (uint8_t *)txt);
        TFTSPI_P8X16Str(3,3,txt,u16RED,u16BLUE);
        
        sprintf(txt,"L11:%3.2fV ",batv3/1000.0f);
        UART_PutStr(LPUART8, (uint8_t *)txt);
        TFTSPI_P8X16Str(3,4,txt,u16RED,u16BLUE);
        
        sprintf(txt,"G12:%3.2fV ",batv4/1000.0f);
        UART_PutStr(LPUART8, (uint8_t *)txt);
        TFTSPI_P8X16Str(3,5,txt,u16RED,u16BLUE);
        
        sprintf(txt,"K12:%3.2fV ",batv5/1000.0f);
        UART_PutStr(LPUART8, (uint8_t *)txt);
        TFTSPI_P8X16Str(3,6,txt,u16RED,u16BLUE);
        
        sprintf(txt,"H11:%3.2fV ",batv6/1000.0f);
        UART_PutStr(LPUART8, (uint8_t *)txt);
        TFTSPI_P8X16Str(3,7,txt,u16RED,u16BLUE);
        
        delayms(100);
    }
}
#endif


