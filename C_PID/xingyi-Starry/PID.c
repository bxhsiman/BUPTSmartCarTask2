#include <stdio.h>
#include "PID.h"

int PID_Init(PID *pid,float target)
{
    pid->kp = 0;
    pid->ki = 0;
    pid->kd = 0;
    pid->err = target;
    pid->sum_err = 0;
    pid->last_err = 0;
    pid->max_err = 0;
}

int PID_SetParameters(PID *pid, float kp, float ki, float kd, float max_err)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->max_err = max_err;
}

int PID_PostionalPID(PID *pid)
{
    float temp_err = pid->err;
    if (pid->err > pid->max_err)
    {
        pid->sum_err += pid->max_err;
        pid->err -= pid->kp * pid->max_err + pid->ki * pid->sum_err + pid->kp * (pid->err - pid->last_err); 
    }
    else
    {
        pid->sum_err += pid->err;
        pid->err -= pid->kp * pid->err + pid->ki * pid->sum_err + pid->kp * (pid->err - pid->last_err);        
    }
    pid->last_err = temp_err;
}