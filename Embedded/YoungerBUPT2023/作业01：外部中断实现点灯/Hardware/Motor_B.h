#ifndef __MOTOR_B_H
#define __MOTOR_B_H

#include "stm32f10x.h"                  // Device header

void Motor_B_PWM_Init(void);
void Motor_BIN1_BIN2_Init(void);
void Motor_B_Speed(int16_t Speed);

#endif
