#include <stdio.h>
#include "PID.h"

int main(void)
{
    float kp,ki,kd;
    PID pid;

    printf("输入本次使用的PID参数\n");
    printf("kp:");
    scanf("%f",&kp);
    getchar();
    printf("ki:");
    scanf("%f",&ki);
    getchar();
    printf("kd:");
    scanf("%f",&kd);
    getchar();

    PID_Init(&pid,100);
    PID_SetParameters(&pid,kp,ki,kd,100);

    printf("普通位置式pid:\n");
    printf("误差表:\n");
    printf("E:%.2f\n",pid.err);
    for (int i = 40;i > 0;i--)
    {
        PID_PostionalPID(&pid);
        printf("E:%.2f\n",pid.err);
    }

    return 0;
}