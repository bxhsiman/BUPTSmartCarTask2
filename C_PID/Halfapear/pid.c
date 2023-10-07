#include "PID.h"

// 初始化PID控制器
int PID_Init(PIDController* pid, float kp, float ki, float kd, float setpoint) {
    pid->kp = kp;             // 设置比例系数
    pid->ki = ki;             // 设置积分系数
    pid->kd = kd;             // 设置微分系数
    pid->setpoint = setpoint; // 设置目标值
    pid->integral = 0;        // 初始化积分累计值为0
    pid->prev_error = 0;      // 初始化上一次误差值为0
    return 0;
}

// 设置PID参数
int PID_SetParameter(PIDController* pid, float kp, float ki, float kd) {
    pid->kp = kp; // 更新比例系数
    pid->ki = ki; // 更新积分系数
    pid->kd = kd; // 更新微分系数
    return 0;
}

// 位置式PID控制
float PID_PositionalPID(PIDController* pid, float input) {
    float error = pid->setpoint - input;   // 计算误差
    pid->integral += error;               // 更新积分累计值
    float derivative = error - pid->prev_error; // 计算误差变化率
    float output = pid->kp * error + pid->ki * pid->integral + pid->kd * derivative; // 计算PID输出
    pid->prev_error = error; // 保存上一次误差值
    return output;
}

// 增量式PID控制
float PID_IncrementalPID(PIDController* pid, float input) {
    float error = pid->setpoint - input;   // 计算误差
    float delta_error = error - pid->prev_error; // 计算误差变化量
    float output = pid->kp * error + pid->ki * delta_error + pid->kd * (delta_error - pid->prev_error); // 计算PID输出
    pid->prev_error = error; // 保存上一次误差值
    return output;
}
