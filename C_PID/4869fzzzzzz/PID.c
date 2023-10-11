#include "PID.h"
void PID_Init(PID_t*pid)
{
    //PID_Init;
    pid->kp        = 0;
    pid->ki        = 0;
    pid->kd        = 0;
    pid->imax      = 0;
    pid->out_p     = 0;
    pid->out_i     = 0;
    pid->out_d     = 0;
    pid->out       = 0;
    pid->target    = 0;
    pid->integrator= 0;
    pid->last_error= 0;
    pid->last_derivative   = 0;
    pid->last_t    = 0;
    pid->fcc_a     = 0;
    pid->fcc_b     = 0;
    pid->pre_error = 0;

}

void PID_SetParameter(PID_t*pid)//设了个默认值，实际看输入
{
    pid->kp        = 1;
    pid->ki        = 0.5;
    pid->kd        = -1;

}

float PID_PostionalPID(PID_t*pid,float error)
{
    /* 累积误差 */
    //默认target=0了
    pid->integrator += error;
    if(pid->integrator>1000)//积分限幅
        pid->integrator=1000;
    if(pid->integrator<-1000)
        pid->integrator=-1000;

    pid->out_p = pid->kp * error;
    pid->out_i = pid->ki * pid->integrator;
    pid->out_d = pid->kd * (error - pid->last_error);

    pid->last_error = error;//更新记录的误差

    pid->out = pid->out_p + pid->out_i + pid->out_d;

    return pid->out;
}

float PID_IncrementalPID(PID_t*pid,float error)
{
    pid->out_p = pid->kp * (error - pid->last_error);
    pid->out_i = pid->ki * error;
    pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);

    pid->last_derivative = error - pid->last_error;
    pid->last_error = error;//更新记录的误差

    pid->out += pid->out_p + pid->out_i + pid->out_d;
    return pid->out;
}

float PID_FeedForwardPID(PID_t*pid,float error)
{
    //没看明白怎么写
    
}








