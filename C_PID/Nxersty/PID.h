#ifndef PID_H
#define PID_H

typedef struct {
    float kp;
    float ki; 
    float kd; 
    float target; 
    float error_sum; 
    float last_error; 
} PID;

int PID_Init(PID *pid, float kp, float ki, float kd, float target);
int PID_SetParameters(PID *pid, float kp, float ki, float kd);
float PID_PositionalPID(PID *pid, float current_value);
float PID_IncrementalPID(PID *pid, float current_value);

#endifm
