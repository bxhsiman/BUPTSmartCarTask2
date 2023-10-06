#include <stdio.h>
#include "PID.h"

float LimitMax(float input,float max)
{
    if (input > max)
    {
        return max;
    }
    else if (input < -max)
    {
        return -max;
    }
    else
    {
        return input;
    }
}

int PID_Init(PID *pid,float target)
{
    pid->kp = 0;
    pid->ki = 0;
    pid->kd = 0;
    pid->err = target;
    pid->sum_err = 0;
    pid->last_err = 0;
    pid->llast_err = 0;
    pid->max_err = 0;
    pid->output = 0;
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
    pid->sum_err += LimitMax(pid->err,pid->max_err);
    pid->output = pid->kp * pid->err + pid->ki * pid->sum_err + pid->kd * (pid->err - pid->last_err);
    pid->last_err = pid->err;
    pid->err -= pid->output; 
}

int PID_IncrementalPID(PID *pid)
{
    pid->output += pid->kp * (pid->err - pid->last_err) + pid->ki * LimitMax(pid->err,pid->max_err) + pid->kd * (pid->err - 2*pid->last_err +pid->llast_err);
    pid->llast_err = pid->last_err;
    pid->last_err = pid->err;
    pid->err -= pid->output;
}