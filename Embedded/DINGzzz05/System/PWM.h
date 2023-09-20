#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"                  // Device header

void PWM_SetCompare(uint16_t Compare);
void PWM_Init(void);

#endif
