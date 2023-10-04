#include<stdio.h>
#include"pid.h"

//限幅函数借鉴了hu同学的思路，我自己尝试写了好几个限幅函数，但似乎只有像hu同学这样宏定义的限幅才有用，我之后会再研究是哪里弄错了，现在先这样
#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }

float sum_max=7000.0;
float result_max=800.0;

void PID_Init(PID* pid)
{
	pid->kp = 0.0;
	pid->ki = 0.0;
	pid->kd = 0.0;
	pid->error = 0.0;
	pid->last_error = 0.0;
	pid->pre_error = 0.0;
	pid->error_sum = 0.0;
	pid->setvalue = 0.0;
	pid->actvalue = 0.0;
	pid->result = 0.0;
}

void PID_SetParameter(float sp, float si, float sd, PID* pid)
{
	pid->kp = sp;
	pid->ki = si;
	pid->kd = sd;
}

float PID_PositionalPID(float set, float act,PID* pid)
{
	pid->setvalue = set;
    pid->actvalue = act;
	pid->error = pid->setvalue - pid->actvalue;
	pid->error_sum += pid->error;
	LimitMax(pid->error_sum, sum_max);
	pid->result = pid->kp * pid->error + pid->ki * pid->error_sum + pid->kd * (pid->error - pid->last_error);
	LimitMax(pid->result, result_max);
	pid->actvalue += pid->result;
	pid->last_error = pid->error;

    return pid->actvalue;
}

float PID_IncrementalPID(float set, float act,PID* pid)
{
	pid->setvalue = set;
    pid->actvalue = act;
	pid->error = pid->setvalue - pid->actvalue;
	float change = pid->kp * (pid->error - pid->last_error) + pid->ki * pid->error + pid->kd * (pid->error - 2 * pid->last_error + pid->pre_error);
	pid->result += change;
	LimitMax(pid->result, result_max);
	pid->actvalue += pid->result;
	pid->pre_error = pid->last_error;
	pid->last_error = pid->error;

    return pid->actvalue;
}