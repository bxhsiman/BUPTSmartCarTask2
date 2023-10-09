#include "pid.h"
#include <stdio.h>
//积分限幅
#define umax 2000
#define umin -2000
//输出限幅
#define omax 1000
#define omin -1000
void PID_Init(PID* pid)
{
    pid->kp = 0;
    pid->ki = 0;
    pid->kd = 0;
    pid->integral = 0;
    pid->err = 0;
    pid->last_err = 0;
    pid->front_err = 0;
    pid->target = 0;
    pid->pwm = 0;
}
int PID_SetParameter(PID* pid, fl kp, fl ki, fl kd,fl target)
{
    if (kp < 0 || ki < 0 || kd < 0)
    {
        return 0;
    }
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->target = target;
    return 1;
}
float PID_PostionalPID(PID* pid, fl pos)
{
    pid->err = pid->target - pos;
    pid->integral += pid->err;
    //积分限幅
    if (pid->integral > umax)
    {
        pid->integral = umax;
    }
    else if (pid->integral < umin)
    {
        pid->integral = umin;
    }
    pid->pwm = pid->kp * pid->err + pid->ki * pid->integral + pid->kd * (pid->err - pid->last_err);
    pid->last_err = pid->err;
    //输出限幅
        if (pid->pwm > omax)
            pid->pwm = omax;
        else if (pid->pwm < omin)
            pid->pwm = omin;
    return pid->pwm;
}
float PID_IncrementalPID(PID* pid, fl pos)
{
    pid->err = pid->target - pos;
    fl tmp = pid->kp * (pid->err - pid->last_err) + pid->ki * pid->err + pid->kd * (pid->err - 2 * pid->last_err + pid->front_err);
    pid->pwm += tmp;
    pid->last_err = pid->err;
    pid->front_err = pid->last_err;
    //输出限幅
    if (pid->pwm > omax)
        pid->pwm = omax;
    else if (pid->pwm < omin)
        pid->pwm = omin;
    return pid->pwm;
}
