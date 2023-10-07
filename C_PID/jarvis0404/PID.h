#include <stdio.h>
#include <stdint.h>

typedef struct
{
    float set;                     // 设定值
    float actual;                  // 实际值
    float err;                     // 误差
    float last_err, last_last_err; // 上一次误差和上上次误差
    float integral;                // 积分
    float kp, ki, kd;              // PID参数
    float PIDOutput;               // PID输出
} PID;

void PID_Init(PID *PIDStruct);                                       // PID初始化
void PID_SetParameter(PID *PIDStruct, float kp, float ki, float kd); // 设置PID参数
float PID_PostionalPID(PID *PIDStruct, float speed);                 // 位置式PID实现
float PID_IncrementalPID(PID *PIDStruct, float speed);               // 增量式PID实现