#include "PID.h"
#include <stdlib.h> 
int PID_Init(PID *pid, float kp, float ki, float kd, float target) {
    if (pid == NULL) return -1; // 检查PID结构体是否为空

    // 初始化PID结构体参数
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->target = target;
    pid->error_sum = 0;
    pid->last_error = 0;

    return 0;
}

int PID_SetParameters(PID *pid, float kp, float ki, float kd) {
    if (pid == NULL) return -1;

    // 设置PID结构体参数
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    return 0;
}

float PID_PositionalPID(PID *pid, float current_value) {
    if (pid == NULL) return 0;

    // 计算误差项
    float error = pid->target - current_value;

    // 计算比例项、积分项、微分项
    float p_term = pid->kp * error;
    pid->error_sum += error;
    float i_term = pid->ki * pid->error_sum;
    float d_term = pid->kd * (error - pid->last_error);

    pid->last_error = error;

    // 计算PID输出
    float output = p_term + i_term + d_term;

    return output;
}

float PID_IncrementalPID(PID *pid, float current_value) {
    if (pid == NULL) return 0; 

    // 计算误差项
    float error = pid->target - current_value;

    // 计算增量式PID输出
    float output = pid->kp * (error - pid->last_error) + pid->ki * error + pid->kd * (error - 2 * pid->last_error + pid->error_sum);

    pid->last_error = error;
    pid->error_sum += error;

    return output;
}
