#define _CRT_SECURE_NO_WARNINGS
#include "pid.h"


static void limit(float* i, float max)
{
    if (*i > max) *i = max;
    if (*i < -max) *i = -max;
}

int PID_Init(PID* pid, float p, float i, float d, float maxI, float maxOut)
{
    pid->kp = p;
    pid->ki = i;
    pid->kd = d;
    pid->maxInteg = maxI;
    pid->maxOutput = maxOut;
    return 0;
}

int PID_SetParameter(PID* pid)
{
    float p, i, d, maxI, maxOut;
    printf("你希望的Kp："); scanf(" %f", &p);
    printf("你希望的Ki："); scanf(" %f",&i);
    printf("你希望的Kd："); scanf(" %f",&d);
    printf("积分限幅："); scanf(" %f",&maxI);
    printf("输出限幅："); scanf(" %f",&maxOut);
    pid->kp = p;
    pid->ki = i;
    pid->kd = d;
    pid->maxInteg = maxI;
    pid->maxOutput = maxOut;
    return 0;
}

int PID_PostionalPID(PID* pid, float target, float current)//位置式PID
{
    pid->lastError = pid->error;
    pid->error = target - current;  // 计算当前误差
    float Poutput = pid->error * pid->kp;//比例
    float Doutput = (pid->error - pid->lastError) * pid->kd;//微分
    pid->integ += pid->ki * pid->error;  // 积分
    pid->integ = pid->integ > pid->maxInteg ? pid->maxInteg : pid->integ;
    pid->integ = pid->integ < -pid->maxInteg ? -pid->maxInteg : pid->integ;
    pid->output = Poutput + Doutput + pid->integ;
    return 0;
}

int PID_IncrementalPID(PID* pid, float target, float current)//增量式PID
{
    pid->priError = pid->lastError;
    pid->lastError = pid->error;
    pid->error = target - current;  // 计算当前误差
    float Poutput = (pid->error - pid->lastError) * pid->kp;//比例
    float Doutput = (pid->error + pid->priError - 2 * pid->lastError) * pid->kd;//微分
    pid->integ = pid->error * pid->ki;//积分
    //pid->integ = pid->integ > pid->maxInteg ? pid->maxInteg:pid->integ;
    //pid->integ = pid->integ < -pid->maxInteg ? -pid->maxInteg : pid->integ;
    limit(&pid->integ, pid->maxInteg);
    pid->output += Poutput + Doutput + pid->integ;
    return 0;
}

int PID_Imitate(float* current, PID* pid)
{
    *current += pid->output;
    return 0;
}

