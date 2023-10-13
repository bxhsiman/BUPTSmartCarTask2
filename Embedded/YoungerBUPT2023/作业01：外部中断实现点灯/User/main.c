#include "stm32f10x.h"                  // Device header
#include "PC13_LED_Test.h"
#include "Steering_Engine.h"
#include "Delay.h"
#include "Infrared_Sensor.h"
#include "OLED.h"
#include "Motor_A.h"
#include "Motor_B.h"
#include "Motor_Move.h"
#include "Key.h"

#define left -1
#define middle 0
#define right 1
#define stop 100

int main()
{
	PC13_LED_Init();
	PC13_LED_OFF();
	
	Key1_Init();
	Key2_Init();
	
	while(1)
	{
		
	}
}