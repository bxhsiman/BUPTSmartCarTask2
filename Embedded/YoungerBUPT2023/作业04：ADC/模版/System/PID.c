#include "PID.h"

Pid Motor1_PID_Contorl;

void Pid_Init(void)
{
	Motor1_PID_Contorl.actual_value = 0.0;
	Motor1_PID_Contorl.err = 0.0;
	Motor1_PID_Contorl.err_last = 0.0;
	Motor1_PID_Contorl.err_sum = 0.0;
	Motor1_PID_Contorl.Kd = 0.0;
	Motor1_PID_Contorl.Ki = 0.0;
	Motor1_PID_Contorl.Kp = 0.0;
	Motor1_PID_Contorl.target_value = 0.0;
}

float P_realize(Pid *pid,float actual_value)
{
	pid->actual_value = actual_value; //传递真实值
	pid->err = pid->target_value - pid->actual_value; //当前误差=目标值-真实值
	pid->actual_value = pid->Kp*(pid->err); //每一次调用函数时，对实际值进行修改
	
	return pid->actual_value;
}

float PI_realize(Pid *pid,float actual_value)
{
	pid->actual_value = actual_value; //当前的真实值
	pid->err = pid->target_value - pid->actual_value; //与目标值之间的误差
	pid->err_sum += pid->err; //累计误差
	pid->actual_value = pid->Kp*(pid->err) + pid->Ki*(pid->err_sum); 
	return pid->actual_value;
}

float PID_realize(Pid *pid,float actual_value)
{
	pid->actual_value = actual_value; //传递当前的真实值
	pid->err = pid->target_value - pid->actual_value; //当前误差
	
	//积分
	pid->err_sum += pid->err; //误差累计值
	pid->actual_value = pid->Kp*(pid->err) + pid->Ki*(pid->err_sum) 
	+ pid->Kd*(pid->err - pid->err_last);  //比例+积分+微分
	
	pid->err_last = pid->err;
	
	return pid->actual_value;
}




