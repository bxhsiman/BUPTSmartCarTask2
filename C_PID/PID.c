#include "PID.h"
#include <time.h>

PID* pid;
PID pid_s;

ERROR error_p;
ERROR error_i;

float target = 100; //目标
float position_p = 0;   
float position_i = 0;

float u_p = 0;//位置pid运算值
float u_i = 0;//增量pid运算值

int ERROR_Init(void)        
{
    error_p.error = 0;
    error_p.pre_error = 0;
    error_p.pre_pre_error = 0;
    error_p.sum_error = 0;
    error_i.error = 0;      
    error_i.pre_error = 0;
    error_i.pre_pre_error = 0;
    error_i.sum_error = 0;
}

int PID_Init(void)
{
    pid = &pid_s;
    pid->kp = 0;
    pid->ki = 0;
    pid->kd = 0;
    return 0;
}

int PID_SetParameter(PID* pid_set)
{
    pid->kp = pid_set->kp;
    pid->ki = pid_set->ki;
    pid->kd = pid_set->kd;
    return 0;
}

int error_get_p(void)
{
    error_p.pre_pre_error = error_p.pre_error;
    error_p.pre_error = error_p.error;
    error_p.error = target - position_p;
    error_p.sum_error += error_p.error;
    return 0;
}

int error_get_i(void)
{
    error_i.pre_pre_error = error_i.pre_error;
    error_i.pre_error = error_i.error;
    error_i.error = target - position_i;
    error_i.sum_error += error_i.error;
    return 0;
}

float PID_PostionalPID(void)
{

    u_p = pid->kp * error_p.error + pid->ki * error_p.sum_error + pid->kd * (error_p.error - error_p.pre_error);
    return u_p;
}

float PID_IncrementalPID(void)
{
    u_i += pid->kp * (error_i.error - error_i.pre_error) + pid->ki * error_i.error + pid->kd * (error_i.error - 2 * error_i.pre_error + error_i.pre_pre_error);
    return u_i;
}

float move_p(float u_p)
{
    position_p += u_p;
    return target - position_p;
}

float move_i(float u_i)
{
    position_i += u_i;
    return target - position_i;
}
