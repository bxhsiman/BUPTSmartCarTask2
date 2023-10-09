#define _CRT_SECURE_NO_WARNINGS
#include "pid.h"


PID pid1, pid2;

int main()
{
	PID_Init(&pid1, 0.5, 0.5, 0.5, 200, 300);
	PID_Init(&pid2, 0.5, 0.5, 0.5, 200, 300);
	int BOOL;
	printf("更改参数？\n    YES->1     NO->0\n");
	scanf(" % d", &BOOL);
	if (BOOL==1)
	{
		printf("以下调整位置式PID参数\n");
		PID_SetParameter(&pid1);
		printf("以下调整增量式PID参数\n");
		PID_SetParameter(&pid2);
	}
	float current1 = 0, current2 = 0;
	const float target = 100;
	srand(time(NULL));
	printf("误差表~~~~^-^~\n");
	while (1)
	{
		PID_PostionalPID(&pid1, target, current1);
		PID_IncrementalPID(&pid2, target, current2);
		PID_Imitate(&current1, &pid1);
		PID_Imitate(&current2, &pid2);
		printf("位置式：%f", pid1.error);printf( "  增量式：%f  \n", pid2.error);
		current1 += rand() % 5;
		current2 += rand() % 5;
		Sleep(5 * 100);
	}
	return 0;
}