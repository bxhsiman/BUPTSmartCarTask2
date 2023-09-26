#include<stdio.h>
#include"pid.h"
#include"pid.c"

int main()
{
    float kp,ki,kd;
    printf("输入本次使用的PID参数\n");
    printf("KP:");
    scanf("%lf",&kp);
    printf("KI:");
    scanf("%lf",&ki);
    printf("KD:");
    scanf("%lf",&kd);

    PID pid1,pid2;
    PID_Init(&pid1);
    PID_Init(&pid2);
    PID_SetParameter(kp,ki,kd,&pid1);
    PID_SetParameter(kp,ki,kd,&pid2);

    float target;
    printf("请输入目标值:");//预期的值
    scanf("%lf",&target);
    float actual;
    printf("请输入当前值:");//目前的值
    scanf("%lf",&actual);
    float actual1,actual2;
    actual1=actual2=actual;

    float pos_err,inc_err;
    printf("普通位置式pid         普通增量式pid\n");
    printf("误差表:\n");

    for(int i=0;i<50;i++)
    {
        actual1=PID_PostionalPID(target,actual1,&pid1);
        actual2=PID_IncrementalPID(target,actual2,&pid2);
        pos_err=pid1.err;
        inc_err=pid2.err;
        printf("E:%-20.2fE:%-.2f\n",pos_err,inc_err);
    }

    return 0;
}