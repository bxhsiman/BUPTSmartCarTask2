#include <stdio.h>
#include "pid.h"
#include <time.h>
#include <stdlib.h>
int main()
{
    int pos1 = 0;              //当前位置
    int pos2 = 0;
    //变量设置
    fl kp, ki, kd, target = 0;
    PID pid1,pid2;
    //初始化
    PID_Init(&pid1);
    PID_Init(&pid2);
    //设置参数
    again:
    printf("请输入目标位置：\n");
    scanf("%f", &target);
    printf("请输入参数：\nkp:");
    scanf("%f", &kp);
    printf("ki:");
    scanf("%f", &ki);
    printf("kd:");
    scanf("%f", &kd);
    //防止设参错误
    int flag1 = 0;
    int flag2 = 0;
    flag1 = PID_SetParameter(&pid1, kp, ki, kd,target);
    flag2 = PID_SetParameter(&pid2, kp, ki, kd, target);
    if (flag1 == 0 || flag2 == 0)
    {
        printf("输入错误\n");
        goto again;
    }
    //模拟
    srand((unsigned int)time(NULL));
    printf("\t误差表\n\n");
    printf("位置式：    增量式：\n");
    int i = 0;
        for (i = 0; i < 100; i++)
        {
            //位置式PID
            pos1 += PID_PostionalPID(&pid1, pos1) + rand() % 10 - 5;
            printf("E:%-10.2f", pid1.err);
            //增量式PID
            pos2 += PID_IncrementalPID(&pid2, pos2) + rand() % 10 - 5;
            printf("E:%-10.2f\n", pid2.err);
        }
        return 0;
}