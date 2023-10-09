#include "stm32f10x.h"                  // Device header
void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//打开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//要给PA0输出，打开PA0
	
	TIM_InternalClockConfig(TIM2);//选择时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//1分频，不过这个分频不重要
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//选择上升计数
	TIM_TimeBaseInitStruct.TIM_Period=100-1;//选择最大值ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler=720-1;//选择分频PRS
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//输出权限归外设，用复用模式
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	//有些参数不用管，一键初始化
	//再单独修改需要修改的参数
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;//使用pwm1模式
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;//高极性，就是不反转
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//打开
	TIM_OCInitStruct.TIM_Pulse=0;//后面呼吸灯CCR还要改，初值是啥无所谓
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);//初始化TIM2的CH1通道
	//注意上述参数不要打成N，那个只能打开高级计时器
	
	TIM_Cmd(TIM2,ENABLE);//打开时钟计数
}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2, Compare);
}
