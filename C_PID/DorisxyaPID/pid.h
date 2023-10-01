#pragma once
typedef struct {
    float ki;
    float kp;
    float kd;
#ifdef PID_integral_ON// 视情况是否采用积分项
    float integral;
    float intergralmax;
#endif


    float Outputmax;//输出最大值
    float intergral; //积分项
    float intergralmax;//积分限幅
    float lasterror;//上一次误差值
    float preverror; //上两次误差值
    float errorsum;//误差累积值
    float Nowposit;
    float Aimposit;


}PID;

int PID_Init(PID* pidtest1);           //初始化PID结构体
float PID_SetParameter (PID* pidtest1,float I, float P,float D,float max);      //设置PID参数
float PID_PostionalPID(PID*pidtest1);      //位置式PID实现
float PID_IncrementalPID(PID*pidtest1);   // 增量式PID实现
