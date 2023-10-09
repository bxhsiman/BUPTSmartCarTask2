#include <stdio.h>
#include "PID.h"

int main() {
    PID pid1, pid2; // 两个pid结构体
    float p, i, d;  // 比例系数、积分系数、微分系数
    float maxI = 1000, maxOut = 1000;   // 最大积分值和最大输出值
    float reference1 = 100, feedback1 = 0;    // 设定值和反馈值
    float reference2 = 100, feedback2 = 0;
    printf("KP:");
    scanf("%f", &p);
    printf("KI:");
    scanf("%f", &i);
    printf("KD:");
    scanf("%f", &d);
    PID_Init(&pid1);        // 初始化pid1
    PID_Init(&pid2);        // 初始化pid2
    PID_SetParameter(&pid1, p, i, d, maxI, maxOut);// 设置pid1参数
    PID_SetParameter(&pid2, p, i, d, maxI, maxOut);// 设置pid2参数
    printf("普通位置式pid\t普通增量式pid\n");
    printf("误差表：\n");   // 打印误差表
    for (int j = 0; j < 20; j++) {
        PID_PostionalPID(&pid1, reference1, feedback1); // 位置式pid1
        printf("E:%.2f  \t", reference1 - feedback1);    // 打印pid1误差
        feedback1 += pid1.output;

        PID_IncrementalPID(&pid2, reference2, feedback2);   // 增量式pid2
        printf("E:%.2f\n", reference2 - feedback2);   // 打印pid2误差
        feedback2 += pid2.output;

    }
            
            

    return 0;   
}