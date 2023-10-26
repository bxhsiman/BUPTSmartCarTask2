#include<stdio.h>
#include"PID.h"
extern PID *pid6;
extern PID pid1, pid2;
extern PID pid;

int main()
{
	extern float kp, ki, kd;
	float dt = 0.001f;
	float dl = 1000.0f;
	float feedback = 0;
	PID_SetParameter();
	PID_Init();
	printf("输入本次使用的PID参数\n");
	printf("kp:");
	scanf_s("%f", &kp);
	printf("ki:");
	scanf_s("%f", &ki); 
	printf("kd:");
	scanf_s("%f", &kd);
	printf("普通位置式pid         普通增量式pid\n误差表：\n");
	for (int i = 0; i < 51; i++)
	{
		pid1.error = pid6->goal - PID_PostionalPID( pid1.feedback, dt,dl); 
		pid2.error = pid6->goal - PID_IncrementalPID( pid2.feedback, dt,dl);

		printf("E:%.2f                E:%.2f\n", pid1.error, pid2.error);
		pid1.feedback = PID_PostionalPID( pid1.feedback, dt,dl);
		pid2.feedback = PID_IncrementalPID( pid2.feedback, dt,dl);

	
	}
	return 0;
}