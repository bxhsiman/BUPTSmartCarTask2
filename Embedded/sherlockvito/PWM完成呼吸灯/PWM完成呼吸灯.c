//PWM完成呼吸灯 灯接在PA0上 用TIM2输出PWM波 使用stm32f103c8t6开发板

#include "stm32f10x.h"                 // Device header
#include "Delay.h"                  

uint16_t i;  

void PWM_Init(void)     
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  //打开时钟
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStucture;                 //定义GPIO结构体
    GPIO_InitStucture.GPIO_Mode =GPIO_Mode_AF_PP;
    GPIO_InitStucture.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStucture);                //初始化GPIO
    
    TIM_InternalClockConfig(TIM2);                      //设置TIM2为内部时钟
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;  //定义TIM结构体
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 100-1;             //ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 720-1;		  //PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);  //初始化TIM2
    
    TIM_OCInitTypeDef TIM_OCInitStructure;            //定义TIM_OC结构体
    TIM_OCStructInit(&TIM_OCInitStructure);           //初始化TIM_OC结构体
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High  ;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; 			  //CCR
    TIM_OC1Init(TIM2,&TIM_OCInitStructure);         //初始化TIM2_OC1    

    TIM_Cmd(TIM2,ENABLE);                       //使能TIM2
}

void PWM_SetCompare1(uint16_t Compare)  //设置PWM的占空比
{
    TIM_SetCompare1(TIM2,Compare);
}

int main(void)
{
    PWM_Init();   // PWM初始化

    while(1)
    {
        for(i=0;i <= 100;i++)   // 从0%占空比变化到100%占空比
        {
            PWM_SetCompare1(i);  
            Delay_ms(10);        
        }
        
        
        for(i=0;i<=100;i++)     // 从100%占空比变化到0%占空比
        {
            PWM_SetCompare1(100 - i);   
            Delay_ms(10);              
        }
    }
}