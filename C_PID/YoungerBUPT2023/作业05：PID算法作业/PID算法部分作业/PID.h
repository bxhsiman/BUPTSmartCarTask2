#ifndef __PID_H
#define __PID_H

typedef struct //声明结构体，来储存PID的每一个参数
{
	float target_value; //目标值
	float actual_value; //实际值
	float err; //当前误差
	float err_last; //上次偏差
	float err_sum; //误差累计值
	float Kp; //比例系数
	float Ki; //积分系数
	float Kd; //微分系数
}Pid;

void Pid_Init(void);

float P_realize(Pid* pid);

float PI_realize(Pid* pid);

float PID_realize(Pid* pid);

void PID_Set_Kp_Ki_Kd(float Kp, float Ki, float Kd);

void PID_Set_Actual_Target(float Actual, float Target);

Pid* Get_pid();

#endif