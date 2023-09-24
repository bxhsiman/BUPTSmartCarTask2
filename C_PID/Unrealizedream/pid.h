#ifndef PID_H
#define PID_H

typedef struct 
{
    float kp ;
    float ki ;
    float kd ;
    float kf ;
    float target ;
    float input ;
    float output ;
    float err ;
    float last_err ;
    float integral ;
} PID;

int PID_Init(PID *pid);             //初始化PID结构体
int PID_SetParameter(float kp, float ki, float kd, float kf ,PID *pid); //设置PID参数
float PID_PostionalPID(PID *pid);      //普通位置式PID实现
float PID_IncrementalPID(PID *pid);    //普通增量式PID实现
float PID_feedforwardPID(PID *pid);    //前馈增量式pid也许实现

#endif