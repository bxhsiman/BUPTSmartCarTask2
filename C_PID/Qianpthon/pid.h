#ifndef __PID_H
#define __PID_H
typedef struct PID
{
	float p,i,d;//比例，积分，微分系数
	float iLimit,outLimit;//积分限幅,输出限幅
	float ek;//当前误差
	float last_ek;//上一次误差
	float pre_ek;//上上次误差
	float out;//输出

}PID;
int PID_Init(PID *pid);             //初始化PID
int PID_SetParameter(float kp, float ki, float kd,  float limit,float outlimit,PID* pid);  //设置PID参数
int PID_PostionalPID(PID* pid,float tar,float pos);      //位置式PID实现
int PID_IncrementalPID(PID* pid,float tar,float pos);    //增量式PID实现
#endif