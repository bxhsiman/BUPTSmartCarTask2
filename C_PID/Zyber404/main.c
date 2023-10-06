#include <stdio.h>
#include "PID.h"
#include <stdlib.h>

int main() {
    PID pid1, pid2, pid3;
    float kp, ki, kd, pos_output, inc_output, ff_output, ff_mid_output;

    // 初始化PID控制器
    PID_Init(&pid1);  
    PID_Init(&pid2);
    PID_Init(&pid3);


    printf("输入本次使用的PID参数:\n");
    printf("KP: ");
    scanf("%f", &kp);
    printf("KI: ");
    scanf("%f", &ki);
    printf("KD: ");
    scanf("%f", &kd);
    printf("普通位置式pid\t普通增量式pid\t前馈增量式pid\n误差表:\n");

    // 设置PID参数
    PID_SetParameter(&pid1, kp, ki, kd);  
    PID_SetParameter(&pid2, kp, ki, kd);
    PID_SetParameter(&pid3, kp, ki, kd);
    pid1.target = 100;
    pid1.max_integral = 100;
    pid1.max_output = 200;
    pid2.target = 100;
    pid2.max_integral = 100;
    pid2.max_output = 200;
    pid3.target = 100;
    pid3.max_integral = 100;
    pid3.max_output = 200;
    ff_mid_output = pid3.output;

    // 模拟PID控制过程
    for (int i = 0; i < 100; i++) {

        // 普通位置式PID
        PID_PostionalPID(&pid1);
        pid1.current = pid1.output;

        // 普通增量式PID
        PID_IncrementalPID(&pid2);
        pid2.current += pid2.output;

        // 前馈增量式PID
        PID_IncrementalPID(&pid3);
        ff_mid_output += pid3.output;
        pid3.current = FeedForward(pid3.target) + ff_mid_output;
        printf("%.2f\t\t%.2f\t\t%.2f\n", pid1.error, pid2.error, pid3.error);
    }
    system("pause");
    return 0;
}
