#include "stm32f10x.h"                  // Device header
#include "Motor_A.h"
#include "Motor_B.h"
#include "OLED.h"
#include "Delay.h"

void Right(void)
{
	Motor_B_Speed(40);
	Motor_A_Speed(0);
	OLED_ShowString(2,1,"__Right");
	Delay_ms(50);
}

void Left(void)
{
	Delay_ms(10);
	Motor_A_Speed(40);
	Motor_B_Speed(0);
	OLED_ShowString(2,1,"___Left");
	Delay_ms(50);
}

void Stright(void)
{
	Delay_ms(10);
	Motor_A_Speed(30);
	Motor_B_Speed(30);
	OLED_ShowString(2,1,"Stright");
	Delay_ms(50);
}
  
void Stop(void)
{
	Delay_ms(10);
	Motor_A_Speed(0);
	Motor_B_Speed(0);
	OLED_ShowString(2,1,"___Stop");
}

