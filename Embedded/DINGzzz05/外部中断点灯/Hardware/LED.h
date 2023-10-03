#ifndef _LED_H
#define _LED_H
#include "stm32f10x.h"                  // Device header

void LED_Init( uint16_t GPIO_Pin);
void LED_On (void);
void LED_Off (void);
void LED_Turn(void);

#endif
