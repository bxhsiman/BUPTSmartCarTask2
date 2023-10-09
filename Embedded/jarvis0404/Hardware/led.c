/*
GPIOB上的LED通用配置函数
*/
#include "stm32f10x.h"

uint16_t LED_Pin;

void LED_Init(uint16_t GPIO_Pin)
{
    LED_Pin = GPIO_Pin;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = LED_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_SetBits(GPIOB, LED_Pin);
}

void LED_On(void)
{
    GPIO_ResetBits(GPIOB, LED_Pin);
}

void LED_Off(void)
{
    GPIO_SetBits(GPIOB, LED_Pin);
}

void LED_Switch(void)
{
    GPIO_WriteBit(GPIOB, LED_Pin, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, LED_Pin)));
}
