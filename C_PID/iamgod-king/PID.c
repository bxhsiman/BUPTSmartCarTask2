#include "PID.h"  //实现PID控制器的功能
PID pid;
PID pid1, pid2;
PID* pid6 = &pid;



float kp, ki, kd = 0;
float PID_Init(void)  //初始化
{
    pid6->Kp = 0.0;
    pid6->Ki = 0.0;
    pid6->Kd = 0.0;
    pid6->goal = 100;  
    return 0;
}

float PID_SetParameter(void)
{
    pid6->Kp = kp;
    pid6->Ki = ki; 
    pid6->Kd = kd;
};

float PID_PostionalPID( float feedback, float dt,float dl)
{
    // 计算当前误差
    pid1.error = pid6->goal - pid1.feedback;

    // 计算积分项
    pid1.integral = pid1.incremental + ki * pid1.error * dt;
    
    // 计算微分项
    float derivative = kd*(pid1.error - pid1.prev_error) / dl;
    
    // 计算输出值
    float output_PostionalPID = kp* pid1.error + pid1.integral + derivative;

    // 更新反馈和误差值
    pid1.incremental = pid1.integral;
    pid1.prev_error = pid1.error;

    return output_PostionalPID;
}


float PID_IncrementalPID(float feedback, float dt,float dl)
{
    // 计算当前误差
    pid2.error = pid6->goal - pid2.feedback;

    // 计算积分项
    pid2.integral = pid2.incremental + ki * pid2.error * dt;

    // 计算微分项
    float derivative = kd * (pid2.error - 2*pid2.prev_error+pid2.prev_prev_error) / dl;

    // 计算输出增量
    float output_IncrementalPID = kp * pid2.error + pid2.integral + derivative;

    // 更新输出增量和反馈值
    pid2.incremental = pid2.integral;
    pid2.prev_prev_error = pid2.prev_error;
    pid2.prev_error = pid2.error;
    return output_IncrementalPID;
}
