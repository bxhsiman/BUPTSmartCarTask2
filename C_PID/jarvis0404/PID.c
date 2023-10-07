#include "PID.h"

void PID_Init(PID *PIDStruct)
{
    PIDStruct->actual = 0.0;
    PIDStruct->set = 0.0;
    PIDStruct->err = 0.0;
    PIDStruct->last_err = 0.0;
    PIDStruct->last_last_err = 0.0;
    PIDStruct->kp = 0.0;
    PIDStruct->ki = 0.0;
    PIDStruct->kd = 0.0;
    PIDStruct->PIDOutput = 0.0;
    PIDStruct->integral = 0.0;
}

void PID_SetParameter(PID *PIDStruct, float kp, float ki, float kd)
{
    PIDStruct->kp = kp;
    PIDStruct->ki = ki;
    PIDStruct->kd = kd;
}

float PID_PostionalPID(PID *PIDStruct, float speed) // 位置式PID实现
{
    PIDStruct->set = speed;
    PIDStruct->err = PIDStruct->set - PIDStruct->actual;
    PIDStruct->integral += PIDStruct->err;
    PIDStruct->PIDOutput = (PIDStruct->kp * PIDStruct->err) + (PIDStruct->ki * PIDStruct->integral) + (PIDStruct->kd * (PIDStruct->err - PIDStruct->last_err));
    PIDStruct->last_err = PIDStruct->err;
    PIDStruct->actual = PIDStruct->PIDOutput * 1.0;

    return PIDStruct->actual;
}

float PID_IncrementalPID(PID *PIDStruct, float set)
{
    PIDStruct->set = set;
    PIDStruct->err = PIDStruct->set - PIDStruct->actual;
    float increment = PIDStruct->kp * (PIDStruct->err - PIDStruct->last_err) + PIDStruct->ki * PIDStruct->err + PIDStruct->kd * (PIDStruct->err - 2 * PIDStruct->last_err + PIDStruct->last_last_err);
    PIDStruct->last_last_err = PIDStruct->last_err;
    PIDStruct->last_err = PIDStruct->err;
    PIDStruct->actual += increment;

    PIDStruct->PIDOutput = PIDStruct->actual * 1.0;

    return PIDStruct->actual;
}

int main(void)
{
    printf("PID Begin\n");
    PID pid;
    PID_Init(&pid);
    PID_SetParameter(&pid, 0.2, 0.015, 0.2);
    uint16_t cnt = 1000;

    while (cnt--)
    {
        printf("PID: %f\n", PID_IncrementalPID(&pid, 100.0));
    }

    return 0;
}
