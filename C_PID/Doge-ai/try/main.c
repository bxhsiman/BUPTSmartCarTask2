//自己从零尝试做了，但是具体公式的实现和模拟的过程没弄明白（甚至感觉因为看了蛮多不同的代码弄混了）
//另外找了一个代码研究和注释，再研究研究先，后面再尝试弄自己的，怕时间到了就打pr了，也顺便把这个失败品发了（
#include <stdio.h>
#include"pid.h"
#include"pid.c" 
int main()
{
    PID pid1,pid2;
    PID_Init(&pid1);
    PID_Init(&pid2);

    float kp,ki,kd;
    printf("输入本次使用的PID参数\n");
    printf("KP:");
    scanf("%lf",&kp);
    printf("KI:");
    scanf("%lf",&ki);
    printf("KD:");
    scanf("%lf",&kd);

    PID_SetParameter(kp,ki,kd,&pid1);
    PID_SetParameter(kp,ki,kd,&pid2);

    float target;
    printf("请输入目标值:");
    scanf("%lf",&target);
    float actual;
    printf("请输入当前值:");
    scanf("%lf",&actual);

    float actual1,actual2;
    actual1=target;
    actual2=target;

    int times =0;
    PID_Init(&pid1);
    PID_Init(&pid1);
    printf("普通位置式pid误差表:              普通增量式pid误差表:\n");
    for(times = 0 ; times<10 ; times++)
    {
        PID_PostionalPID(target,actual1,&pid1);
        PID_IncrementalPID(target,actual2,&pid2);
        Limit_i(&pid1);
        Limit_i(&pid2);
        printf("E=%2f                        E=%2f\n",pid1.err,pid2.err);
    }
   
    return 0;
}