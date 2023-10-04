#ifndef _BUZZER_H
#define _BUZZER_H
#include "stm32f10x.h"                  // Device header

void Buzzer_Init( uint16_t GPIO_Pin);
void Buzzer_Set ( uint16_t GPIO_Pin, BitAction BitVal);

#endif
