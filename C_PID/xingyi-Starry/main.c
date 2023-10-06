//我承认我有借鉴其他同学的成分，望学长手下留情
//前馈还没整，主要是在最基本的模型中（目标值不变）前馈和微分好像没什么区别。。

#include <stdio.h>
#include "PID.h"

int main(void)
{
    float kp,ki,kd,max_err,target,i;
    PID pid1,pid2;

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
    printf("max_err:");
    scanf("%f",&max_err);
    getchar();
    printf("target:");
    scanf("%f",&target);
    getchar();
    printf("循环次数:");
    scanf("%f",&i);
    getchar();

    PID_Init(&pid1,target);
    PID_Init(&pid2,target);
    PID_SetParameters(&pid2,kp,ki,kd,max_err);
    PID_SetParameters(&pid1,kp,ki,kd,max_err);

    printf("普通位置式pid:     普通增量式pid\n");
    printf("误差表:\n");
    printf("E:%6.2f           %6.2f\n",pid1.err,pid2.err);
    for (;i > 0;i--)
    {
        PID_PostionalPID(&pid1);
        PID_IncrementalPID(&pid2);
        printf("E:%6.2f           %6.2f\n",pid1.err,pid2.err);
    }

    return 0;
}
