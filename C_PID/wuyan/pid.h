#pragma once
#ifndef __PID_H
#define __PID_H




#include <stdio.h>
#include<time.h>
#include<windows.h>
typedef struct
{
    float kp, ki, kd;
    float error, lastError, priError;//误差、上次误差、上上次误差
    float integ, maxInteg;//积分、积分限幅
    float output, maxOutput;//输出、输出限幅
}PID;

//初始化结构体(默认值p=1,i=0.5,d=0.1,maxI=200,maxOut=300)
int PID_Init(PID* pid, float p, float i, float d, float maxI, float maxOut);

//调整参数
int PID_SetParameter(PID* pid);

//位置式PID
int PID_PostionalPID(PID* pid, float target, float current);

//增量式PID
int PID_IncrementalPID(PID* pid, float target, float current);

//模拟外界误差并返回current
int PID_Imitate(float* current, PID* pid);

#endif // !__PID_H