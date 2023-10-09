#include "pid.h"

//初始化PID
int PID_Init(PID* pid) {
	pid->p = 0;
	pid->i = 0; 
	pid->d = 0;
	pid->iLimit = 1000;
	pid->outLimit = 1000;
	pid->ek = 0;
	pid->last_ek = 0;
	pid->pre_ek = 0;
	pid->out = 0;
	return 0;
}
//设置PID参数
int PID_SetParameter(float kp, float ki, float kd, float ilimit,float outlimit, PID* pid)
{
	pid->p = kp;
	pid->i = ki;
	pid->d = kd;
	pid->iLimit = ilimit;
	pid->outLimit=outlimit;
	return 0;
}

//位置式PID实现
int PID_PostionalPID(PID* pid, float tar, float pos) {
	pid->last_ek = pid->ek;
	pid->ek = tar -pos;
	float P = pid->p * pid->ek;
	float D=pid->d*(pid->ek-pid->last_ek);
	float I=0;
	I+=pid->i*pid->ek;
	if(I>pid->iLimit)
		I=pid->iLimit;
	else if(I<-pid->iLimit)
		I=-pid->iLimit;
	pid->out=P+I+D;
	if(pid->out>pid->outLimit)
		pid->out=pid->outLimit;
	else if(pid->out<-pid->outLimit)
		pid->out=-pid->outLimit;
	return 0;
};
//增量式PID实现
int PID_IncrementalPID(PID* pid, float tar, float pos) {
	pid->pre_ek = pid->last_ek;
	pid->last_ek = pid->ek;
	pid->ek = tar - pos;
	float P = pid->p * (pid->ek - pid->last_ek);
	float D = pid->d * (pid->ek - 2 * pid->last_ek + pid->pre_ek);
	float I = pid->i * pid->ek;
	pid->out += P + I + D;
	if (pid->out > pid->outLimit)
		pid->out = pid->outLimit;
	else if (pid->out < -pid->outLimit)
		pid->out = -pid->outLimit;
	
	return 0;
}
