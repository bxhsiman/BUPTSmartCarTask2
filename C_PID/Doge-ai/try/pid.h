#pragma once
#ifndef _PID_H_
#define _PID_H_

typedef struct 
{
    float LastOut,out;//输出
    float inte;//积分
    float kp,ki,kd;//比例积分微分系数
    float target;//目标值
    float actual;//实际值
    float errSum;//误差和
    float err;//误差s
    float errLast;//上次误差

  
} PID;

    int PID_Init(PID*pid);       //初始化PID结构体
    int PID_SetParameter(float kp, float ki, float kd, PID*pid);  //设置PID参数
    int PID_PostionalPID(float target, float actual, PID*pid);      //位置式PID实现
    int PID_IncrementalPID(float target, float actual, PID*pid);    //增量式PID实现
   
    #endif