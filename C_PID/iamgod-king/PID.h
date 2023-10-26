#pragma once
#ifndef _PID_H_
#define _PID_H_


typedef struct 
{
	float Kp;
	float Ki;
	float Kd;

	float goal;       //目标
	float feedback;   //反馈
	float prev_feedback;//上一次反馈

	float error;
	float integral;    // 积分项累加值
	float prev_error;  // 上一次误差值
	float prev_prev_error;//上上次误差

	float incremental;  //增量

}PID;        



float PID_Init(void);             //初始化PID结构体
float PID_SetParameter(void);      //设置PID参数
float PID_PostionalPID(float feedback, float dt,float dl);      //位置式PID实现
float PID_IncrementalPID(float feedback, float dt,float dl);    //增量式PID实现

#endif