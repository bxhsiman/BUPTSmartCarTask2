#include <stdio.h>
#include <stdint.h>

typedef struct
{
    float set;
    float actual;
    float err;
    float last_err;
    float kp, ki, kd;
    float voltage;
    float integral;
} PID;

void PID_Init(PID *PIDStruct)
{
    PIDStruct->actual = 0.0;
    PIDStruct->set = 0.0;
    PIDStruct->err = 0.0;
    PIDStruct->last_err = 0.0;
    PIDStruct->kp = 0.0;
    PIDStruct->ki = 0.0;
    PIDStruct->kd = 0.0;
    PIDStruct->voltage = 0.0;
    PIDStruct->integral = 0.0;
}

void PID_SetParameter(PID *PIDStruct, float kp, float ki, float kd); // 设置PID参数
float PID_PostionalPID(PID *PIDStruct, float speed);
int PID_IncrementalPID(PID *PIDStruct); // 增量式PID实现

int main(void)
{
    printf("PID Begin\n");
    PID pid;
    PID_Init(&pid);
    PID_SetParameter(&pid, 0.2, 0.015, 0.2);
    uint16_t cnt = 1000;
    while (cnt--)
    {
        printf("PID: %f\n", PID_PostionalPID(&pid, 100.0));
    }
    return 0;
}

float PID_PostionalPID(PID *PIDStruct, float speed) // 位置式PID实现
{
    PIDStruct->set = speed;
    PIDStruct->err = PIDStruct->set - PIDStruct->actual;
    PIDStruct->integral += PIDStruct->err;
    PIDStruct->voltage = (PIDStruct->kp * PIDStruct->err) + (PIDStruct->ki * PIDStruct->integral) + (PIDStruct->kd * (PIDStruct->err - PIDStruct->last_err));
    PIDStruct->last_err = PIDStruct->err;
    PIDStruct->actual = PIDStruct->voltage * 1.0;

    return PIDStruct->actual;
}

void PID_SetParameter(PID *PIDStruct, float kp, float ki, float kd)
{
    PIDStruct->kp = kp;
    PIDStruct->ki = ki;
    PIDStruct->kd = kd;
}