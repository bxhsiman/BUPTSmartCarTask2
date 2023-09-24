// 使用c语言实现位置式和增量式PID控制器
#include "pid.h"
// 初始化PID
void PID_Init(PID *pp, float kp, float ki, float kd, float maxError, float maxSumError)
{
    pp->kp = kp;
    pp->ki = ki;
    pp->kd = kd;
    pp->maxError = maxError; // 误差上限
    pp->maxSumError = maxSumError; // 积分上限
    pp->lastError = 0;
    pp->sumError = 0; // 误差累计
    pp->lastLastError = 0;
}
// 设置PID参数
int PID_SetParameters(PID *pp, float kp, float ki, float kd, float maxError, float maxSumError)
{
    if (kp < 0 || ki < 0 || kd < 0 || maxError < 0 || maxSumError < 0)
    {
        return -1;
    }
    pp->kp = kp;
    pp->ki = ki;
    pp->kd = kd;
    pp->maxError = maxError;
    pp->maxSumError = maxSumError;
    return 0;
}

// 位置式PID实现
int PID_PostionalPID(PID *pp, float target, float measure, float *output, float *error)
{
    *error = target - measure;
    float increment = 0;
    if (*error > pp->maxError)
    {
        *error = pp->maxError;
    }
    else if (*error < -pp->maxError)
    {
        *error = -pp->maxError;
    }
    pp->sumError += *error;
    if (pp->sumError > pp->maxSumError)
    {
        pp->sumError = pp->maxSumError;
    }
    else if (pp->sumError < -pp->maxSumError)
    {
        pp->sumError = -pp->maxSumError;
    }
    increment = pp->kp * (*error) + pp->ki * pp->sumError + pp->kd * (*error - pp->lastError);
    pp->lastError = *error;
    *output += increment;
    return 0;
}

// 增量式PID实现
int PID_IncrementalPID(PID *pp, float target, float measure, float *output, float *error)
{
    *error = target - measure;
    float increment = 0;
    if (*error > pp->maxError)
    {
        *error = pp->maxError;
    }
    else if (*error < -pp->maxError)
    {
        *error = -pp->maxError;
    }
    increment = pp->kp * (*error - pp->lastError) + pp->ki * (*error) + pp->kd * (*error - 2 * pp->lastError + pp->lastLastError);
    pp->lastLastError = pp->lastError;
    pp->lastError = *error;
    *output += increment;
    return 0;
}

