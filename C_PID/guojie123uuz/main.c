#include<stdio.h>
#include"pid.c"
#include"pid.h"

int main()
{
    PID pid1,pid2;
    PID_Init(&pid1);
    PID_Init(&pid2);

    float kp,ki,kd;
    printf("输入本次使用的PID参数:\n");
    printf("Kp:");
    scanf("%lf",&kp);
    printf("Ki:");
    scanf("%lf",&ki);
    printf("Kd:");
    scanf("%lf",&kd);

    PID_SetParameter(kp,ki,kd,&pid1);
    PID_SetParameter(kp,ki,kd,&pid2);

    float set;
    printf("请输入目标值:");
    scanf("%lf",&set);
    float act;
    printf("请输入当前值:");
    scanf("%lf",&act);

    float act1,act2;
    act1=act;
    act2=act;

    printf("普通位置式pid         普通增量式pid\n");
    printf("误差表:\n");

    for(int i=0;i<40;i++)
    {
        act1=PID_PositionalPID(set,act1,&pid1);
        act2=PID_IncrementalPID(set,act2,&pid2);
        printf("E:%-15.2fE:%-.2f\n",pid1.error,pid2.error);
    }

    return 0;
}