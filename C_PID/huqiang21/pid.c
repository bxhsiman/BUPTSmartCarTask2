#include<stdio.h>
#include"pid.h"

//限幅函数
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

#define summax 10000        //积分项限幅
#define resultmax 1000      //结果项限幅

int PID_Init(PID*pid)
{
    pid->kp=0.0;
    pid->ki=0.0;
    pid->kd=0.0;
    pid->err=0.0;
    pid->target=0.0;
    pid->last_err=0.0;
    pid->sum=0.0;
    pid->pos_result=0.0;
    pid->err_diff=0.0;
    pid->inc_result=0.0;
    pid->delt_inc_result=0.0;
    pid->prior_err=0.0;
    pid->d=0.0;
    pid->actual=0.0;
    return 0;
}

int PID_SetParameter(float p, float i, float d, PID*pid)
{
    pid->kp=p;
    pid->ki=i;
    pid->kd=d;
    return 0;
}

float PID_PostionalPID(float target, float actual, PID*pid)
{

    pid->target=target;
    pid->actual=actual;

    pid->err=pid->target-pid->actual;
    pid->sum=pid->sum+pid->err;
    LimitMax(pid->sum,summax);
    pid->err_diff=pid->err-pid->last_err;
    pid->pos_result=pid->kp*pid->err+pid->ki*pid->sum+pid->kd*pid->err_diff;
    LimitMax(pid->pos_result,resultmax)

    pid->actual+=pid->pos_result;
    pid->last_err=pid->err;
    return pid->actual;     //返回调整之后的值
}

float PID_IncrementalPID(float target, float actual, PID*pid)
{
    pid->target=target;
    pid->actual=actual;

    pid->err=pid->target-pid->actual;
    pid->err_diff=pid->err-pid->last_err;
    pid->d=pid->err-2*pid->last_err+pid->prior_err;
    pid->delt_inc_result=pid->kp*pid->err_diff+pid->ki*pid->err+pid->kd*pid->d;
    pid->inc_result+=pid->delt_inc_result;
    LimitMax(pid->inc_result,resultmax)
    
    pid->actual+=pid->inc_result;
    pid->prior_err=pid->last_err;
    pid->last_err=pid->err;
    return pid->actual;
}

