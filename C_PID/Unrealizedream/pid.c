#include"pid.h"
#include<stdio.h>


int PID_Init(PID *pid)
{
    pid->target = 100;
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
int PID_SetParameter(float kp, float ki, float kd, float kf ,PID *pid)
{
    printf("请输入参数,例如1.0\n");
    printf("kp= ");
    scanf("%1f",&kp) ;
    getchar();
    getchar();
    printf("ki= ") ;
    scanf("%1f",&ki) ;
    getchar();
    getchar();
    printf("kd= ");
    scanf("%1f",&kd) ;
    getchar();
    getchar();
    printf("kf= ");
    scanf("%1f",&kf);
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

int main()
{
    PID pid ;
    float kp = 0;
    float ki = 0;
    float kd = 0;
    float kf = 0;
    PID_Init(&pid);
    PID_SetParameter(kp, ki, kd, kf,&pid);
    int times = 0 ;
    printf("普通位置式pid误差表:\n");
    for(times = 0 ; times<10 ; times++)
    {
        PID_PostionalPID(&pid);
        Limit_i(&pid);
        printf("E=%2f\n",pid.err);
    };
    
    times = 0 ;
    PID_Init(&pid);
    printf("普通增量式pid误差表:\n");
    for(times = 0 ; times<10 ; times++)
    {
        PID_IncrementalPID(&pid);
        Limit_i(&pid);
        printf("E=%2f\n",pid.err);
    };
    
    times = 0 ;
    PID_Init(&pid);
    printf("前馈式pid误差表:\n");
    for(times = 0 ; times<10 ; times++)
    {
        PID_feedforwardPID(&pid);
        Limit_i(&pid);
        printf("E=%2f\n",pid.err);
    };
    
    return 0;
}