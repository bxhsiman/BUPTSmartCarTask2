// 单独创建一个main.c用来模拟执行你的PID控制器
#include "pid.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
    PID pp;
    float target = 100;
    float measure1 = 0;float measure2 = 0;
    float output1 = 0;float output2 = 0;
    float error1 = 0;float error2 = 0;
    float ki,kp,kd;
    printf("请输入本次kp,ki,kd的值:\n");
    scanf("kp:%f", &kp);
    scanf("ki:%f", &ki);
    scanf("kd:%f", &kd);
    PID_Init(&pp, kp, ki, kd, 100, 100);
    printf("位置式PID误差表    增量式PID误差表\n");
    while (1)
    {
        // 输出位置式PID控制器的误差表
        PID_PostionalPID(&pp, target, measure1, &output1, &error1);
        printf("%-10f         ", error1);
        measure1 = output1;
        if (fabs(target - measure1) < 0.01)
        {
            break;
        }
         // 输出增量式PID控制器的误差表
        PID_IncrementalPID(&pp, target, measure2, &output2, &error2);
        printf("%f\n", error2);
        measure2 = output2;
        if (fabs(target - measure2) < 0.01)
        {
            break;
        }
    }
    return 0;
}