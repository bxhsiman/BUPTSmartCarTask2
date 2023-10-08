#include<iostream>
using namespace std;
typedef struct {
    float setpoint;
    float kp, ki, kd;
    float prev_error;
    float integral;
    float prev_control;
} PIDController;

void PID_Init(PIDController* pid);    //初始化PID结构体
void PID_SetParameter(PIDController* pid, float kp, float ki, float kd);     //设置PID参数
float PID_PostionalPID(PIDController* pid, float pv);    //位置式PID实现
float PID_IncrementalPID(PIDController* pid, float pv);    //增量式PID实现#pragma once
