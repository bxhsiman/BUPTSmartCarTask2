#include<stdio.h>
#include "pid.h"
int main()
{
    float kp, ki, kd;
    printf("输入本次使用的PID参数\n");
    printf("KP:");
    scanf("%lf",&kp);
    printf("KI:");
    scanf("%lf",&ki);
    printf("KD:");
    scanf("%lf",&kd);

    PID my_pid;
    float current_value; 
    float target;
    printf("请输入目标值:"); // 预期的值
    scanf("%lf",&target);
    printf("请输入当前值:"); // 目前的值
    scanf("%lf",&current_value);

    float pos_err,inc_err;
    printf("普通位置式pid         普通增量式pid\n");
    printf("误差表:\n");

    // 初始化PID结构体
    PID_Init(&my_pid, kp, ki, kd, target);
    PID_SetParameters(&my_pid, kp, ki, kd);


    // 模拟执行PID控制器
    for (int i = 0; i < 10; ++i) {
        current_value += 5; // 模拟当前值增加

        // 位置式PID控制
        float pos_pid_output = PID_PositionalPID(&my_pid, current_value);
        // 增量式PID控制
        float inc_pid_output = PID_IncrementalPID(&my_pid, current_value);

        printf("E:%.2f         E:%.2f\n",pos_pid_output,inc_pid_output);
        
    }

    return 0;
}
