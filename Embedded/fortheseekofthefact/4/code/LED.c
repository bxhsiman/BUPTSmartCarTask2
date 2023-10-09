/*-----------------------------------------------------------------
homework2
--------------------------------------------------------------------*/
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "LQ_LED.h"
#include "LQ_GPIO.h"

/* ÉùÃ÷Íâ²¿ÑÓÊ±º¯Êý */
extern void delayms(uint16_t ms);


#if 0   //Ê¹ÓÃfsl¿â£¬ÎÊ¾ÍÊÇconfig toolsµ¼ÈëÔÙÐÞ¸ÄµÎ

void LED_Init(void)
{    
    CLOCK_EnableClock(kCLOCK_Iomuxc);           // ´ò¿ªIO¿ÚÊ±ÖÓ
    /*       ºËÐÄ°åÉÏµÄLED       */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_GPIO2_IO23, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_GPIO3_IO26, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_41_GPIO3_IO27, 0U);
    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_07_GPIO2_IO23,0x10B0u);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_40_GPIO3_IO26,0x10B0u);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_41_GPIO3_IO27,0x10B0u);
    
    //Êä³ö¿Ú¹Ü½ÅÅäÖÃ½á¹¹Ìå
    gpio_pin_config_t GPIO_Output_Config = {kGPIO_DigitalOutput, //GPIOÎªÊä³ö·½Ïò
                                            0,                   //µÍµçÆ½
                                            kGPIO_NoIntmode      //·ÇÖÐ¶ÏÄ£Ê½
                                            };  
    
    GPIO_PinInit(GPIO2,23, &GPIO_Output_Config);     //B12  ºËÐÄ°åGµÆ
    GPIO_PinInit(GPIO3,26, &GPIO_Output_Config);     //A7   ºËÐÄ°åRµÆ   
    GPIO_PinInit(GPIO3,27, &GPIO_Output_Config);     //C7   ºËÐÄ°åBµÆ
    
    /*             Ä¸°åÉÏµÄlEDÒý½Å             */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_GPIO2_IO22, 0U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_04_GPIO1_IO04, 0U);
    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_06_GPIO2_IO22,0x10B0u);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_04_GPIO1_IO04,0x10B0u);
    
    GPIO_PinInit(GPIO2,22, &GPIO_Output_Config);      //C12  µÆD0
    GPIO_PinInit(GPIO1,04, &GPIO_Output_Config);      //F11  µÆD1
    
}
/*Ö¸¶¨ÑÕÉ«µÄµÆÁÁ*/
void LED_Color(LED_t color)
{
    switch(color)
    {
        case white:
            GPIO_PinWrite(GPIO2,23, 0U);//LEDÁÁ; 
            GPIO_PinWrite(GPIO3,26, 0U);//LEDÁÁ; 
            GPIO_PinWrite(GPIO3,27, 0U);//LEDÁÁ; 
            break;
        case black:
            GPIO_PinWrite(GPIO2,23, 1U);//LEDÃð; 
            GPIO_PinWrite(GPIO3,26, 1U);//LEDÃð; 
            GPIO_PinWrite(GPIO3,27, 1U);//LEDÃð; 
            break;
        case red:
            GPIO_PinWrite(GPIO2,23, 1U);//LEDÃð; 
            GPIO_PinWrite(GPIO3,26, 0U);//LEDÁÁ; 
            GPIO_PinWrite(GPIO3,27, 1U);//LEDÃð; 
            break;
        case green:
            GPIO_PinWrite(GPIO2,23, 0U);//LEDÁÁ; 
            GPIO_PinWrite(GPIO3,26, 1U);//LEDÃð; 
            GPIO_PinWrite(GPIO3,27, 1U);//LEDÃð; 
            break;
        case blue:
            GPIO_PinWrite(GPIO2,23, 1U);//LEDÃð; 
            GPIO_PinWrite(GPIO3,26, 1U);//LEDÃð; 
            GPIO_PinWrite(GPIO3,27, 0U);//LEDÁÁ; 
            break;
        case yellow:
            GPIO_PinWrite(GPIO2,23, 0U);//LEDÁÁ; 
            GPIO_PinWrite(GPIO3,26, 0U);//LEDÁÁ; 
            GPIO_PinWrite(GPIO3,27, 1U);//LEDÃð; 
            break;
        case violet:
            GPIO_PinWrite(GPIO2,23, 1U);//LEDÃð; 
            GPIO_PinWrite(GPIO3,26, 0U);//LEDÁÁ; 
            GPIO_PinWrite(GPIO3,27, 0U);//LEDÁÁ; 
            break;
        case cyan:
            GPIO_PinWrite(GPIO2,23, 0U);//LEDÁÁ; 
            GPIO_PinWrite(GPIO3,26, 1U);//LEDÃð; 
            GPIO_PinWrite(GPIO3,27, 0U);//LEDÁÁ; 
            break;      
    }
}




#else  //Ê¹ÓÃ·â×°¹ýµÄº¯Êý²Ù×÷LED

/*RGBµÆÒý½Å³õÊ¼»¯*/
void LED_Init(void)
{
    PIN_InitConfig(B12, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(A7,  PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(C7,  PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(C12, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(F11, PIN_MODE_OUTPUT, 0);
    
}

/*Ö¸¶¨ÑÕÉ«µÄµÆÁÁ*/
void LED_Color(LED_t color)
{
    switch(color)
    {
        case white:
            PIN_Write(B12, 0U);//LEDÁÁ; 
            PIN_Write(A7,  0U);//LEDÁÁ; 
            PIN_Write(C7,  0U);//LEDÁÁ; 
            break;
        case black:
            PIN_Write(B12, 1U);//LEDÃð; 
            PIN_Write(A7,  1U);//LEDÃð; 
            PIN_Write(C7,  1U);//LEDÃð; 
            break;
        case red:
            PIN_Write(B12, 1U);//LEDÃð; 
            PIN_Write(A7,  0U);//LEDÁÁ; 
            PIN_Write(C7,  1U);//LEDÃð; 
            break;
        case green:
            PIN_Write(B12, 0U);//LEDÁÁ; 
            PIN_Write(A7,  1U);//LEDÃð; 
            PIN_Write(C7,  1U);//LEDÃð; 
            break;
        case blue:
            PIN_Write(B12, 1U);//LEDÃð; 
            PIN_Write(A7,  1U);//LEDÃð; 
            PIN_Write(C7,  0U);//LEDÁÁ; 
            break;
        case yellow:
            PIN_Write(B12, 0U);//LEDÁÁ; 
            PIN_Write(A7,  0U);//LEDÁÁ; 
            PIN_Write(C7,  1U);//LEDÃð; 
            break;
        case violet:
            PIN_Write(B12, 1U);//LEDÃð; 
            PIN_Write(A7,  0U);//LEDÁÁ; 
            PIN_Write(C7,  0U);//LEDÁÁ; 
            break;
        case cyan:
            PIN_Write(B12, 0U);//LEDÁÁ; 
            PIN_Write(A7,  1U);//LEDÃð; 
            PIN_Write(C7,  0U);//LEDÁÁ; 
            break;      
    }
}



#endif

/*Ö¸¶¨ÑÕÉ«ÉÁË¸*/
void LED_ColorReverse(LED_t color)
{
    static uint8_t count = 0;
    if(count++ % 2)
    {
        LED_Color(color);   //ÁÁÖ¸¶¨ÑÕÉ«µÄµÆ
    }
    else
    {
        LED_Color(black);   //Ãð
    }
    
}

void Test_LED(void)
{
  LED_Init();   
  while (1)
  {          
         LED_Color(red);     //ºìµÆ
        delayms(500);
        LED_Color(green);   //ÂÌµÆ
        delayms(500);
        LED_Color(blue);    //À¶µÆ
        delayms(500);
        LED_Color(violet);  //×ÏµÆ
        delayms(500);
        LED_Color(yellow);  //»ÆµÆ
        delayms(500);
        LED_Color(cyan);    //ÇàµÆ
        delayms(500);
        LED_Color(white);   //°×µÆ
        delayms(500);
        LED_Color(black);   //¹ØµÆ
        delayms(500);
        
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(red);     //ºìµÆÉÁË¸
            delayms(200);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(green);   //ÂÌµÆÉÁË¸
            delayms(200);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(blue);    //À¶µÆÉÁË¸
            delayms(200);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(violet);  //×ÏµÆÉÁË¸
            delayms(200);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(yellow);  //»ÆµÆÉÁË¸
            delayms(200);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(cyan);    //ÇàµÆÉÁË¸
            delayms(200);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(white);   //°×µÆÉÁË¸
            delayms(200);
        }
        
        for(int i = 0; i < 20; i++)
        {
            GPIO_PinWrite(GPIO1,4, 1U);   //Ä¸°åLED0ÉÁË¸
            GPIO_PinWrite(GPIO2,22, 1U);  //Ä¸°åLED1ÉÁË¸
            delayms(100);
            GPIO_PinWrite(GPIO1,4, 0U);   //Ä¸°åLED0ÉÁË¸
            GPIO_PinWrite(GPIO2,22, 0U);  //Ä¸°åLED1ÉÁË¸
            delayms(100);
        }

  }
}


