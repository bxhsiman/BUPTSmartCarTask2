#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_Angle(uint16_t angle)
{
	PWM_SetCompare(((angle*180)/45)+180);
}
