#include"pid.h"
#include<stdio.h>

int main()
{
    PID pid ;
    float kp = 0;
    float ki = 0;
    float kd = 0;
    float kf = 0;
    PID_Init(&pid);
    PID_SetParameter(kp, ki, kd, kf,&pid);
    int times = 0 ;
    printf("普通位置式pid误差表:\n");
    for(times = 0 ; times<10 ; times++)
    {
        PID_PostionalPID(&pid);
        Limit_i(&pid);
        printf("E=%2f\n",pid.err);
    };
    
    times = 0 ;
    PID_Init(&pid);
    printf("普通增量式pid误差表:\n");
    for(times = 0 ; times<10 ; times++)
    {
        PID_IncrementalPID(&pid);
        Limit_i(&pid);
        printf("E=%2f\n",pid.err);
    };
    
    times = 0 ;
    PID_Init(&pid);
    printf("前馈式pid误差表:\n");
    for(times = 0 ; times<10 ; times++)
    {
        PID_feedforwardPID(&pid);
        Limit_i(&pid);
        printf("E=%2f\n",pid.err);
    };
    
    return 0;
}