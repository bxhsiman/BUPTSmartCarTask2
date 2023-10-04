#ifndef PID_H
#define PID_H

typedef struct
{
	float kp;
	float ki;
	float kd;
	float error;
	float last_error;
	float pre_error;
	float error_sum;
	float setvalue;
	float actvalue;
	float result;
} PID;

void PID_Init(PID* pid);                                                      //初始化PID结构体
void PID_SetParameter(float sp, float si, float sd, PID* pid);                //设置PID参数
float PID_PositionalPID(float set, float act,PID* pid);                 //位置式PID实现
float PID_IncrementalPID(float set, float act,PID* pid);                //增量式PID实现

#endif