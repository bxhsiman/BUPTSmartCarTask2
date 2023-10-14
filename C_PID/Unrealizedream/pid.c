#include"pid.h"
#include<stdio.h>

float PID_Init(PID *pid)
{
    pid->target = 50;
    pid->input =0;
    pid->output = 0;
    pid->err = 0;
    pid->last_err = 0;
    pid->integral = 0;
    return 0;
};             //初始化PID结构体

int Limit_i(PID *pid)
{
    if (pid->integral > 200);
        pid->integral = 200 ;
    if (pid->integral <= 200);
        pid->integral = 200 ;
    return 0;//对i进行限制
}
float PID_SetParameter(float kp, float ki, float kd, float kf ,PID *pid)
{
    printf("请输入参数,例如1.0\n");
    printf("kp= ");
    scanf("%f",&kp) ;
    getchar();
    printf("ki= ") ;
    scanf("%f",&ki) ;
    getchar();
    printf("kd= ");
    scanf("%f",&kd) ;
    getchar();
    printf("kf= ");
    scanf("%f",&kf);
    pid->kp = kp ;
    pid->ki = ki ;
    pid->kd = kd ;
    pid->kf = kf ;
};      //设置PID参数

float PID_PostionalPID(PID *pid)
{
    pid->err = pid->target - pid->output ;
    pid->integral += pid->err ;
    pid->input = pid->kp *pid->err + pid->ki*pid->integral + pid->kd*(pid->last_err - pid->err);
    pid->output +=  pid->input ;
    pid->last_err = pid->err ;
};      //普通位置式PID实现
float PID_IncrementalPID(PID *pid)
{
    pid->err = pid->target - pid->output ;
    pid->integral += pid->err ;
    pid->input = pid->kp * (pid->last_err - pid->err) + pid->ki*pid->integral + pid->kd* (pid->last_err - pid->err);
    pid->output += pid->input  ;
    pid->last_err= pid->err ;
};    //普通增量式PID实现
float PID_feedforwardPID(PID *pid)
{
    pid->err = pid->target - pid->output ;
    pid->integral += pid->err ;
    pid->input = pid->kp * (pid->last_err - pid->err) + pid->ki*pid->integral + pid->kd * (pid->last_err - pid->err) + pid->kf * pid->target;
    pid->output += pid->input  ;
    pid->last_err= pid->err ;
};    //前馈增量式pid实现

