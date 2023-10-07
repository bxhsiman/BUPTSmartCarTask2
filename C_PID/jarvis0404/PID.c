#include <stdio.h>
#include <stdint.h>

typedef struct
{
    float set;
    float actual;
    float err;
    float err_last;
    float kp, ki, kd;
    float voltage;
    float integral;
} PID;

void PID_Init(PID *pidStruct)
{
    pidStruct->actual = 0.0;
    pidStruct->set = 0.0;
    pidStruct->err = 0.0;
    pidStruct->err_last = 0.0;
    pidStruct->kp = 0.0;
    pidStruct->ki = 0.0;
    pidStruct->kd = 0.0;
    pidStruct->voltage = 0.0;
    pidStruct->integral = 0.0;
}

int PID_SetParameter(PID *pidStruct); // 设置PID参数
float PID_PostionalPID(PID *pidStruct, float speed);
int PID_IncrementalPID(PID *pidStruct); // 增量式PID实现

int main(void)
{

    return 0;
}

float PID_PostionalPID(PID *pidStruct, float speed) // 位置式PID实现
{
    pidStruct->set = speed;
    pidStruct->err = pidStruct->set - pidStruct->actual;
    pidStruct->integral += pidStruct->err;
    pidStruct->voltage = (pidStruct->kp * pidStruct->err) + (pidStruct->ki * pidStruct->integral) + (pidStruct->kd * (pidStruct->err - pidStruct->err_last));
    pidStruct->err_last = pidStruct->err;
    pidStruct->actual = pidStruct->voltage * 1.0;

    return pidStruct->actual;
}

int PID_IncrementalPID(PID *pidStruct)
{
}