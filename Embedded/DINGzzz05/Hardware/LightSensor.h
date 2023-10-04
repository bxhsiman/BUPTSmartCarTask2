#ifndef _LIGHTSENSOR_H
#define _LIGHTSENSOR_H
#include "stm32f10x.h"                  // Device header

void LightSensor_Init (uint16_t GPIO_Pin);
uint8_t LightSensor_Get (void);

#endif
