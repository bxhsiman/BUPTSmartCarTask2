#ifndef PID_H
#define PID_H

typedef struct
{
    float ki;
    float kp;
    float kd;
}PID;

typedef struct
{
    float error;
    float pre_error;
    float pre_pre_error;
    float sum_error;
}ERROR;

int PID_Init(void);//初始化PID结构

int ERROR_Init(void);//初始化error

int PID_SetParameter(PID* pid_set);      //设置PID参数

float PID_PostionalPID(void);      //位置式PID实现
float PID_IncrementalPID(void);    //增量式PID实现

int error_get_p(void);//error获取
int error_get_i(void);

float move_p(float u_p);//移动
float move_i(float u_i);



#endif