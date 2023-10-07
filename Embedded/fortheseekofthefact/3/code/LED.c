/*-----------------------------------------------------------------
homework2
--------------------------------------------------------------------*/
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "LQ_LED.h"
#include "LQ_GPIO.h"

/* �����ⲿ��ʱ���� */
extern void delayms(uint16_t ms);


#if 0   //ʹ��fsl�⣬�ʾ���config tools�������޸ĵ�

void LED_Init(void)
{    
    CLOCK_EnableClock(kCLOCK_Iomuxc);           // ��IO��ʱ��
    /*       ���İ��ϵ�LED       */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_GPIO2_IO23, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_GPIO3_IO26, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_41_GPIO3_IO27, 0U);
    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_07_GPIO2_IO23,0x10B0u);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_40_GPIO3_IO26,0x10B0u);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_41_GPIO3_IO27,0x10B0u);
    
    //����ڹܽ����ýṹ��
    gpio_pin_config_t GPIO_Output_Config = {kGPIO_DigitalOutput, //GPIOΪ�������
                                            0,                   //�͵�ƽ
                                            kGPIO_NoIntmode      //���ж�ģʽ
                                            };  
    
    GPIO_PinInit(GPIO2,23, &GPIO_Output_Config);     //B12  ���İ�G��
    GPIO_PinInit(GPIO3,26, &GPIO_Output_Config);     //A7   ���İ�R��   
    GPIO_PinInit(GPIO3,27, &GPIO_Output_Config);     //C7   ���İ�B��
    
    /*             ĸ���ϵ�lED����             */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_GPIO2_IO22, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_04_GPIO1_IO04, 0U);
    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_06_GPIO2_IO22,0x10B0u);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_04_GPIO1_IO04,0x10B0u);
    
    GPIO_PinInit(GPIO2,22, &GPIO_Output_Config);      //C12  ��D0
    GPIO_PinInit(GPIO1,04, &GPIO_Output_Config);      //F11  ��D1
    
}
/*ָ����ɫ�ĵ���*/
void LED_Color(LED_t color)
{
    switch(color)
    {
        case white:
            GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED��; 
            break;
        case black:
            GPIO_PinWrite(GPIO2,23, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED��; 
            break;
        case red:
            GPIO_PinWrite(GPIO2,23, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED��; 
            break;
        case green:
            GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED��; 
            break;
        case blue:
            GPIO_PinWrite(GPIO2,23, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED��; 
            break;
        case yellow:
            GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 1U);//LED��; 
            break;
        case violet:
            GPIO_PinWrite(GPIO2,23, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED��; 
            break;
        case cyan:
            GPIO_PinWrite(GPIO2,23, 0U);//LED��; 
            GPIO_PinWrite(GPIO3,26, 1U);//LED��; 
            GPIO_PinWrite(GPIO3,27, 0U);//LED��; 
            break;      
    }
}




#else  //ʹ�÷�װ���ĺ�������LED

/*RGB�����ų�ʼ��*/
void LED_Init(void)
{
    PIN_InitConfig(B12, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(A7,  PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(C7,  PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(C12, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(F11, PIN_MODE_OUTPUT, 0);
    
}

/*ָ����ɫ�ĵ���*/
void LED_Color(LED_t color)
{
    switch(color)
    {
        case white:
            PIN_Write(B12, 0U);//LED��; 
            PIN_Write(A7,  0U);//LED��; 
            PIN_Write(C7,  0U);//LED��; 
            break;
        case black:
            PIN_Write(B12, 1U);//LED��; 
            PIN_Write(A7,  1U);//LED��; 
            PIN_Write(C7,  1U);//LED��; 
            break;
        case red:
            PIN_Write(B12, 1U);//LED��; 
            PIN_Write(A7,  0U);//LED��; 
            PIN_Write(C7,  1U);//LED��; 
            break;
        case green:
            PIN_Write(B12, 0U);//LED��; 
            PIN_Write(A7,  1U);//LED��; 
            PIN_Write(C7,  1U);//LED��; 
            break;
        case blue:
            PIN_Write(B12, 1U);//LED��; 
            PIN_Write(A7,  1U);//LED��; 
            PIN_Write(C7,  0U);//LED��; 
            break;
        case yellow:
            PIN_Write(B12, 0U);//LED��; 
            PIN_Write(A7,  0U);//LED��; 
            PIN_Write(C7,  1U);//LED��; 
            break;
        case violet:
            PIN_Write(B12, 1U);//LED��; 
            PIN_Write(A7,  0U);//LED��; 
            PIN_Write(C7,  0U);//LED��; 
            break;
        case cyan:
            PIN_Write(B12, 0U);//LED��; 
            PIN_Write(A7,  1U);//LED��; 
            PIN_Write(C7,  0U);//LED��; 
            break;      
    }
}



#endif

/*ָ����ɫ��˸*/
void LED_ColorReverse(LED_t color)
{
    static uint8_t count = 0;
    if(count++ % 2)
    {
        LED_Color(color);   //��ָ����ɫ�ĵ�
    }
    else
    {
        LED_Color(black);   //��
    }
    
}

void Test_LED(void)
{
  LED_Init();   
  while (1)
  {          
         LED_Color(red);     //���
        delayms(500);
        LED_Color(green);   //�̵�
        delayms(500);
        LED_Color(blue);    //����
        delayms(500);
        LED_Color(violet);  //�ϵ�
        delayms(500);
        LED_Color(yellow);  //�Ƶ�
        delayms(500);
        LED_Color(cyan);    //���
        delayms(500);
        LED_Color(white);   //�׵�
        delayms(500);
        LED_Color(black);   //�ص�
        delayms(500);
        
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(red);     //�����˸
            delayms(200);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(green);   //�̵���˸
            delayms(200);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(blue);    //������˸
            delayms(200);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(violet);  //�ϵ���˸
            delayms(200);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(yellow);  //�Ƶ���˸
            delayms(200);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(cyan);    //�����˸
            delayms(200);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(white);   //�׵���˸
            delayms(200);
        }
        
        for(int i = 0; i < 20; i++)
        {
            GPIO_PinWrite(GPIO1,4, 1U);   //ĸ��LED0��˸
            GPIO_PinWrite(GPIO2,22, 1U);  //ĸ��LED1��˸
            delayms(100);
            GPIO_PinWrite(GPIO1,4, 0U);   //ĸ��LED0��˸
            GPIO_PinWrite(GPIO2,22, 0U);  //ĸ��LED1��˸
            delayms(100);
        }

  }
}


