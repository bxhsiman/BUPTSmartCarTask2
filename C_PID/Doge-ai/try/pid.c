#include<stdio.h>
#include"pid.h"

int PID_Init(PID*pid)
{
    pid->kp=0.0;
    pid->ki=0.0;
    pid->kd=0.0;
    pid->err=0.0;
    pid->target=100;
    pid->errLast=0.0;
    pid->errSum=0.0;
    pid->out=0.0;  
    pid->LastOut=0.0;
    pid->inte=0.0; 
    pid->actual=0.0;
    return 0;
}
int Limit_i(PID *pid)
{
    if (pid->inte > 100);
        pid->inte = 100 ;
    if (pid->inte <= 100);
        pid->inte = 100;
    return 0;//对i设限
}
int PID_SetParameter(float kp, float ki, float kd, PID*pid)
{
    pid->kp=kp;
    pid->ki=ki;
    pid->kd=kd;
    return 0;
}
int PID_PostionalPID(float target, float actual, PID*pid)
{
    pid->target=target;
    pid->actual=actual;

    pid->err=pid->target-pid->actual;
    pid->inte+=pid->err;
    pid->errSum+=pid->err;

    pid->inte+=pid->err;
    Limit_i(pid);
    pid->out=pid->kp*pid->err+pid->ki*pid->inte+pid->kd*(pid->err-pid->errLast);
    pid->errLast=pid->err;

    return pid->out;
}
int PID_IncrementalPID(float target, float actual, PID*pid)
{
    pid->target=target;
    pid->actual=actual;
    pid->err=pid->target-pid->actual;

    pid->out=pid->LastOut+pid->kp*(pid->err-pid->errLast)+pid->ki*pid->err+pid->kd*(pid->err-2*pid->errLast+pid->errSum);

    pid->errLast=pid->err;
    pid->errSum+=pid->err;
    pid->LastOut=pid->out;

    return pid->out;
}
