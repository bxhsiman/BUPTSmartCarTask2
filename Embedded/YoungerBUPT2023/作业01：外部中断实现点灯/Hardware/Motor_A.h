#ifndef __MOTOR_A_H
#define __MOTOR_A_H

#include "stm32f10x.h"                  // Device header

void Motor_A_PWM_Init(void);
void Motor_AIN1_AIN2_Init(void);
void Motor_A_Speed(int16_t Speed);

#endif
