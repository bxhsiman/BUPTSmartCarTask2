#pragma once
#ifndef _PID_H
#define _PID_H

typedef struct {

	float
		output,           //输出值
		target,           //目标值
		current,          //实际值
		error,            //误差值
		error_sum,        //积分值
		error_last,       //上次误差值
		error_llast,      //上上次误差值
		error_sum_max,    //积分限幅
		Kp, Ki, Kd;       //PID系数

}PID;

PID* PID_Init();              //初始化PID结构体
PID* PID_SetParameter(PID* popid);      //设置PID参数
void PID_PostionalPID(PID* pid);      //位置式PID实现
void PID_IncrementalPID(PID* pid);    //增量式PID实现

#endif
