#include "stm32f10x.h" 				// Device header
#include "Delay.h"

void LED_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void KEY_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

int main(void){
	LED_Init();
	KEY_Init();
	while(1){
		uint8_t input = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
		if(input == 0){
			GPIO_SetBits(GPIOA,GPIO_Pin_0);
		}else{
			GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		}
	}
}
