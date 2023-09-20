#ifndef _KEY_H
#define _KEY_H
#include "stm32f10x.h"                  // Device header

void Key_Init (void);
void EXTI0_IRQHandler(void);
#endif
