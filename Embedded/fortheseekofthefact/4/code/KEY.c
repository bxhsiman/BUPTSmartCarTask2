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
/* �����ⲿ��ʱ���� */
extern void delayms(uint16_t ms);


#if  1   //ʹ��fsl�� ����GPIO

void KEY_Init(void)
{  
    CLOCK_EnableClock(kCLOCK_Iomuxc);                    // IO��ʱ��ʹ��
    
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,0U);//�ܽ�P2
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_GPIO3_IO00,0U);//�ܽ�L5
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_GPIO1_IO01,0U);//�ܽ�H10
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_00_GPIO3_IO00,0xF080); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_01_GPIO1_IO01,0xF080);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,0xF080);
    
    //һ������ڹܽŶ���
    gpio_pin_config_t GPIO_Input_Config = {kGPIO_DigitalInput,    //GPIOΪ���뷽��
                                            1,                    //�ߵ�ƽ
                                            kGPIO_NoIntmode,      //�������ж�
                                            };
    
    GPIO_PinInit(GPIO3,  0, &GPIO_Input_Config);        // GPIO����ڣ����ж�
    GPIO_PinInit(GPIO1,  1, &GPIO_Input_Config);        // GPIO����ڣ����ж�
    GPIO_PinInit(GPIO3,  4, &GPIO_Input_Config);        // GPIO����ڣ����ж�
    
}

uint8_t KEY_Read(uint8_t mode)
{
    static uint8_t key_up=1;     //�����ɿ���־
    if(mode==1) 
    {
        key_up=1;      //֧������
    }
    if(key_up && (GPIO_PinRead(GPIO3, 4)==0 || GPIO_PinRead(GPIO3, 0)==0 || GPIO_PinRead(GPIO1, 1)==0))
    {
        delayms(10);   //����
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
    return 0;   //�ް�������
    
}

void Test_ExtiKEY(void)
{
    LED_Init();
    
    /*GPIO �ⲿ�ж����ÿ�ʼ*/
    CLOCK_EnableClock(kCLOCK_Iomuxc);                         // IO��ʱ��ʹ��
    gpio_pin_config_t GPIO_Input_Config =                     // GPIO��ʼ���ṹ��
    {
        .direction = kGPIO_DigitalInput,                      // ����
        .outputLogic = 0U,                                  
        .interruptMode = kGPIO_IntFallingEdge                 // �½����ж�
    };
    
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_00_GPIO3_IO00,0U);        // ���ùܽŸ��ù���                          
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_00_GPIO3_IO00,0x90B0U);// ���ùܽ� ���� 
    GPIO_PinInit(GPIO3, 0U, &GPIO_Input_Config);                 // GPIO����ڣ����� �½��ش����ж�
    GPIO_PortEnableInterrupts(GPIO3,1<<0);			             // L5 GPIO3_00�ж�ʹ��
    
    
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_GPIO1_IO01,0U);        // ���ùܽŸ��ù���                          
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_01_GPIO1_IO01,0x90B0U);// ���ùܽ� ����
    GPIO_PinInit(GPIO1, 1U, &GPIO_Input_Config);                 // GPIO����ڣ����� �½��ش����ж�   
    GPIO_PortEnableInterrupts(GPIO1,1<<1);			             // H10 GPIO1_01�ж�ʹ��
 
    
    IOMUXC_SetPinMux(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,0U);        // ���ùܽŸ��ù���                          
    IOMUXC_SetPinConfig(IOMUXC_GPIO_SD_B1_04_GPIO3_IO04,0x90B0U);// ���ùܽ� ����
    GPIO_PinInit(GPIO3, 4U, &GPIO_Input_Config);                 // GPIO����ڣ����� �½��ش����ж�   
    GPIO_PortEnableInterrupts(GPIO3,1<<4);			             // P2 GPIO3_4�ж�ʹ��
    
    
    //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
    NVIC_SetPriority(GPIO3_Combined_0_15_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
	EnableIRQ(GPIO3_Combined_0_15_IRQn);			          //ʹ��GPIO3_0~15IO���ж�  
    
    //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
    NVIC_SetPriority(GPIO1_Combined_0_15_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
	EnableIRQ(GPIO1_Combined_0_15_IRQn);			          //ʹ��GPIO1_0~15IO���ж� 
    /*GPIO �ⲿ�ж����ý���*/  
    
    /* ��irq.c �� �����ж� */
    while(1);
}


#else //ʹ�÷�װ����fsl�����GPIO

void KEY_Init(void)
{  
    /* ������������ */
    PIN_InitConfig(P2,  PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(L5,  PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(H10, PIN_MODE_INPUT_PULLUP, 1);  
}


uint8_t KEY_Read(uint8_t mode)
{
    static uint8_t key_up=1;     //�����ɿ���־
    if(mode==1) 
    {
        key_up=1;      //֧������
    }
    if(key_up && (PIN_Read(P2)==0 || PIN_Read(L5)==0 || PIN_Read(H10)==0))
    {
        delayms(10);   //����
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
    return 0;   //�ް�������
    
}


void Test_ExtiKEY(void)
{
    LED_Init();
    
    /* �����½��ش����ж� */
    PIN_Exti(L5,  PIN_IRQ_MODE_FALLING);
    PIN_Exti(H10, PIN_IRQ_MODE_FALLING);
    PIN_Exti(P2,  PIN_IRQ_MODE_FALLING);
    
    //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
    NVIC_SetPriority(GPIO3_Combined_0_15_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
	EnableIRQ(GPIO3_Combined_0_15_IRQn);			          //ʹ��GPIO3_0~15IO���ж�  
    
    //���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
    NVIC_SetPriority(GPIO1_Combined_0_15_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
	EnableIRQ(GPIO1_Combined_0_15_IRQn);			          //ʹ��GPIO1_0~15IO���ж� 
    /*GPIO �ⲿ�ж����ý���*/  
    
    /* ��irq.c �� �����ж� */
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


