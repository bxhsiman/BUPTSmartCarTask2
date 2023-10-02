#ifndef __PID_H
#define __PID_H

typedef struct {
	float kp;
	float ki;
	float kd;
    float kf; //前馈参数
	float target;
    float last_target;
	float pos;
	float last_err;
    float integral;
}PID;

int PID_Init(PID *pid);            //初始化PID结构体
int PID_SetParameter(float kp, float ki, float kd,float kf, PID* pid);     //设置PID参数
int PID_SetTarget(float target,PID* pid);    //设置下一个目标位置
float PID_PostionalPID(PID* pid);    //位置式PID实现
float PID_IncrementalPID(PID* pid);    //增量式PID实现
float PID_FeedforwardIncrementalPID(PID* pid);  //前馈式增量PID实现

#endif