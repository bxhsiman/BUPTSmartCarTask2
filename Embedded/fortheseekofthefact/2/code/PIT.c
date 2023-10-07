#include "fsl_pit.h"
#include "LQ_GPIO_Cfg.h"
#include "LQ_PIT.h"

void PIT_InitConfig(pit_chnl_t channel, uint32_t count)
{
    static uint8_t pit_count = 0;
    
    /* 防止PIT多次初始化 */
    if(pit_count == 0)
    {
        pit_count++;
        
        /* PIT初始化结构体 */
        pit_config_t pitConfig;                
        
        /*
        * pitConfig.enableRunInDebug = false;  
        */
        PIT_GetDefaultConfig(&pitConfig);   //获取默认参数
        
        pitConfig.enableRunInDebug = false;
        PIT_Init(PIT, &pitConfig);          //初始化PIT
        
        //优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断
        NVIC_SetPriority(PIT_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
        
        /* Enable at the NVIC */
        EnableIRQ(PIT_IRQn);                //使能中断
        
    }
 
    /* 设置PIT通道和定时时间 PIT默认使用IPG时钟的二分频 75M时钟 */
    PIT_SetTimerPeriod(PIT, channel, USEC_TO_COUNT(count, CLOCK_GetFreq(kCLOCK_IpgClk)/2)); 
    
    //清除中断标志位
    PIT_ClearStatusFlags(PIT, channel, kPIT_TimerFlag); 
    
    //使能通道中断
    PIT_EnableInterrupts(PIT, channel, kPIT_TimerInterruptEnable);  

    //开启定时器
    PIT_StartTimer(PIT, channel);   
    
    if(channel == kPIT_Chnl_1)
    {
        PIT_StopTimer(PIT, channel);   
            
        PIT->CHANNEL[1].TCTRL = 0x03;
        
        /* 设置PIT通道和定时时间 PIT默认使用IPG时钟的二分频 75M时钟 */
        PIT_SetTimerPeriod(PIT, channel, USEC_TO_COUNT(count, CLOCK_GetFreq(kCLOCK_IpgClk)/2)); 
        
        //清除中断标志位
        PIT_ClearStatusFlags(PIT, channel, kPIT_TimerFlag); 
        
        //使能通道中断
        PIT_EnableInterrupts(PIT, channel, kPIT_TimerInterruptEnable);  
        
        //开启定时器
        PIT_StartTimer(PIT, channel); 
    }
}

