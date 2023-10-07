/*-----------------------------------------------------------------
realize
--------------------------------------------------------------------*/
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "LQ_LED.h"
#include "LQ_KEY.h"
#include "LQ_GPIO.h"
/* 声明外部延时函数 */
extern void delayms(uint16_t ms);


#if  1   //使用fsl库 操作GPIO

void KEY_Init(void)
{  
    CLOCK_EnableClock(kCLOCK_Iomuxc);                    // IO口时钟使能
    
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,0U);//管脚P2
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_GPIO3_IO00,0U);//管脚L5
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_GPIO1_IO01,0U);//管脚H10
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_00_GPIO3_IO00,0xF080); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_01_GPIO1_IO01,0xF080);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,0xF080);
    
    //一般输入口管脚定义
    gpio_pin_config_t GPIO_Input_Config = {kGPIO_DigitalInput,    //GPIO为输入方向
                                            1,                    //高电平
                                            kGPIO_NoIntmode,      //不触发中断
                                            };
    
    GPIO_PinInit(GPIO3,  0, &GPIO_Input_Config);        // GPIO输入口，非中断
    GPIO_PinInit(GPIO1,  1, &GPIO_Input_Config);        // GPIO输入口，非中断
    GPIO_PinInit(GPIO3,  4, &GPIO_Input_Config);        // GPIO输入口，非中断
    
}

uint8_t KEY_Read(uint8_t mode)
{
    static uint8_t key_up=1;     //按键松开标志
    if(mode==1) 
    {
        key_up=1;      //支持连按
    }
    if(key_up && (GPIO_PinRead(GPIO3, 4)==0 || GPIO_PinRead(GPIO3, 0)==0 || GPIO_PinRead(GPIO1, 1)==0))
    {
        delayms(10);   //消抖
        key_up=0;
        if(GPIO_PinRead(GPIO3, 4)==0)      
        {
            return 1;
        }
        
        else if(GPIO_PinRead(GPIO3, 0)==0) 
        {
            return 2;    
        }
        
        else if(GPIO_PinRead(GPIO1,  1)==0) 
        {
            return 3;    
        }
        
    }
    if(GPIO_PinRead(GPIO3, 4)==1 && GPIO_PinRead(GPIO3, 0)==1 && GPIO_PinRead(GPIO1,  1)==1) 
    {
        key_up=1;   
    }
    return 0;   //无按键按下
    
}

void Test_ExtiKEY(void)
{
    LED_Init();
    
    /*GPIO 外部中断配置开始*/
    CLOCK_EnableClock(kCLOCK_Iomuxc);                         // IO口时钟使能
    gpio_pin_config_t GPIO_Input_Config =                     // GPIO初始化结构体
    {
        .direction = kGPIO_DigitalInput,                      // 输入
        .outputLogic = 0U,                                  
        .interruptMode = kGPIO_IntFallingEdge                 // 下降沿中断
    };
    
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_GPIO3_IO00,0U);        // 设置管脚复用功能                          
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_00_GPIO3_IO00,0x90B0U);// 配置管脚 上拉 
    GPIO_PinInit(GPIO3, 0U, &GPIO_Input_Config);                 // GPIO输入口，上拉 下降沿触发中断
    GPIO_PortEnableInterrupts(GPIO3,1<<0);			             // L5 GPIO3_00中断使能
    
    
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_GPIO1_IO01,0U);        // 设置管脚复用功能                          
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_01_GPIO1_IO01,0x90B0U);// 配置管脚 上拉
    GPIO_PinInit(GPIO1, 1U, &GPIO_Input_Config);                 // GPIO输入口，上拉 下降沿触发中断   
    GPIO_PortEnableInterrupts(GPIO1,1<<1);			             // H10 GPIO1_01中断使能
 
    
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,0U);        // 设置管脚复用功能                          
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,0x90B0U);// 配置管脚 上拉
    GPIO_PinInit(GPIO3, 4U, &GPIO_Input_Config);                 // GPIO输入口，上拉 下降沿触发中断   
    GPIO_PortEnableInterrupts(GPIO3,1<<4);			             // P2 GPIO3_4中断使能
    
    
    //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
    NVIC_SetPriority(GPIO3_Combined_0_15_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
	EnableIRQ(GPIO3_Combined_0_15_IRQn);			          //使能GPIO3_0~15IO的中断  
    
    //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
    NVIC_SetPriority(GPIO1_Combined_0_15_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
	EnableIRQ(GPIO1_Combined_0_15_IRQn);			          //使能GPIO1_0~15IO的中断 
    /*GPIO 外部中断配置结束*/  
    
    /* 在irq.c 中 处理中断 */
    while(1);
}


#else //使用封装过的fsl库操作GPIO

void KEY_Init(void)
{  
    /* 设置上拉输入 */
    PIN_InitConfig(P2,  PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(L5,  PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(H10, PIN_MODE_INPUT_PULLUP, 1);  
}


uint8_t KEY_Read(uint8_t mode)
{
    static uint8_t key_up=1;     //按键松开标志
    if(mode==1) 
    {
        key_up=1;      //支持连按
    }
    if(key_up && (PIN_Read(P2)==0 || PIN_Read(L5)==0 || PIN_Read(H10)==0))
    {
        delayms(10);   //消抖
        key_up=0;
        if(PIN_Read(P2)==0)      
        {
            return 1;
        }
        
        else if(PIN_Read(L5)==0) 
        {
            return 2;    
        }
        
        else if(PIN_Read(H10)==0) 
        {
            return 3;    
        }
        
    }
    if(PIN_Read(P2)==1 && PIN_Read(L5)==1 && PIN_Read(H10)==1) 
    {
        key_up=1;   
    }
    return 0;   //无按键按下
    
}


void Test_ExtiKEY(void)
{
    LED_Init();
    
    /* 配置下降沿触发中断 */
    PIN_Exti(L5,  PIN_IRQ_MODE_FALLING);
    PIN_Exti(H10, PIN_IRQ_MODE_FALLING);
    PIN_Exti(P2,  PIN_IRQ_MODE_FALLING);
    
    //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
    NVIC_SetPriority(GPIO3_Combined_0_15_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
	EnableIRQ(GPIO3_Combined_0_15_IRQn);			          //使能GPIO3_0~15IO的中断  
    
    //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
    NVIC_SetPriority(GPIO1_Combined_0_15_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
	EnableIRQ(GPIO1_Combined_0_15_IRQn);			          //使能GPIO1_0~15IO的中断 
    /*GPIO 外部中断配置结束*/  
    
    /* 在irq.c 中 处理中断 */
    while(1);



}
#endif


void Test_KEY(void)
{ 
    LED_Init();
    KEY_Init(); 
    while (1)
    {  
        switch(KEY_Read(1))  
        {
            case 1:
                LED_Color(red);     
                break;           
            case 2:      
                LED_Color(green);   
                break;
            case 3:      
                LED_Color(blue);    
                break;
            default:
                LED_Color(black);   
                break;
        }

        delayms(50);
    }
}


