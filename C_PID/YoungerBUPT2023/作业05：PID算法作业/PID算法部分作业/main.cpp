#include<stdio.h>
#include"PID.h"
int main()
{
	float value;
	int count = 0;
	int cou = 0;
	float acu = 3.0;

	Pid_Init();
	PID_Set_Kp_Ki_Kd(0.1, 0.5, 0.2);
	PID_Set_Actual_Target(acu, 10);

	while (true)
	{
		cou++;
		if (cou >= 10000000)
		{
			value = PID_realize(Get_pid());
			printf("%f\n", value);
			cou = 0;
			count++;
		}
		
		if (count >= 100)
		{
			printf("COUNTCOUNTCOUT\n");
			printf("COUNTCOUNTCOUT\n");
			printf("COUNTCOUNTCOUT\n");
			printf("COUNTCOUNTCOUT\n");
			printf("COUNTCOUNTCOUT\n");
			count = 0;
			acu++;
			PID_Set_Actual_Target(acu, 10);
		}
	}
}
	