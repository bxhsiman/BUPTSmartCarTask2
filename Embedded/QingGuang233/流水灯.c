#include "stm32f10x.h" 				// Device header
#include "Delay.h"



int main(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	int i = 0;
	while (1)
	{
		if(i >= 8){
			i = 0;
		}
		GPIO_Write(GPIOA, 0x0001 << i);	//0000 0000 0000 0001
		Delay_ms(100);
		i++;
	}
	
}
