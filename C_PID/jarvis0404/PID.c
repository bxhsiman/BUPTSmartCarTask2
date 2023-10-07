#include "PID.h"

void PID_Init(PID *PIDStruct)
{
    PIDStruct->actual = 0.0;
    PIDStruct->target = 0.0;
    PIDStruct->err = 0.0;
    PIDStruct->last_err = 0.0;
    PIDStruct->last_last_err = 0.0;
    PIDStruct->kp = 0.2;
    PIDStruct->ki = 0.015;
    PIDStruct->kd = 0.2;
    PIDStruct->PIDOutput = 0.0;
    PIDStruct->sum = 0.0;
}

void PID_SetParameter(PID *PIDStruct, float kp, float ki, float kd)
{
    PIDStruct->kp = kp;
    PIDStruct->ki = ki;
    PIDStruct->kd = kd;
}

float PID_PostionalPID(PID *PIDStruct, float target) // 位置式PID实现
{
    PIDStruct->target = target;
    PIDStruct->err = PIDStruct->target - PIDStruct->actual;
    PIDStruct->sum += PIDStruct->err;
    PIDStruct->PIDOutput = (PIDStruct->kp * PIDStruct->err) + (PIDStruct->ki * PIDStruct->sum) + (PIDStruct->kd * (PIDStruct->err - PIDStruct->last_err));
    PIDStruct->last_err = PIDStruct->err;
    PIDStruct->actual = PIDStruct->PIDOutput * 1.0;

    return PIDStruct->actual;
}

float PID_IncrementalPID(PID *PIDStruct, float target)
{
    PIDStruct->target = target;
    PIDStruct->err = PIDStruct->target - PIDStruct->actual; // 当前误差
    float increment = PIDStruct->kp * (PIDStruct->err - PIDStruct->last_err) + PIDStruct->ki * PIDStruct->err + PIDStruct->kd * (PIDStruct->err - 2 * PIDStruct->last_err + PIDStruct->last_last_err);
    PIDStruct->last_last_err = PIDStruct->last_err; // 更新上上次误差
    PIDStruct->last_err = PIDStruct->err;           // 更新上次误差
    PIDStruct->actual += increment;                 // 更新实际值

    PIDStruct->PIDOutput = PIDStruct->actual * 1.0; // PID Controller输出

    return PIDStruct->actual;
}

int main(void)
{
    printf("PID Begin\n");
    PID pid;
    PID_Init(&pid);

    uint16_t cnt = 1000;

    printf("普通位置式PID | 增量式PID\n");
    while (cnt--)
    {
        printf("PID: %f | ", PID_PostionalPID(&pid, 100.0));
        printf("PID: %f\n", PID_IncrementalPID(&pid, 100.0));
    }

    return 0;
}
