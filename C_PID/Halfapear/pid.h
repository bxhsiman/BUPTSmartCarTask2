#ifndef PID_H
#define PID_H

typedef struct {
    float kp;
    float ki;
    float kd;
    float setpoint;
    float integral;
    float prev_error;
} PIDController;

int PID_Init(PIDController* pid, float kp, float ki, float kd, float setpoint);
//初始化PID结构体
int PID_SetParameter(PIDController* pid, float kp, float ki, float kd);
//设置PID参数
float PID_PositionalPID(PIDController* pid, float input);
//位置式PID实现
float PID_IncrementalPID(PIDController* pid, float input);
//增量式PID实现

#endif // PID_H