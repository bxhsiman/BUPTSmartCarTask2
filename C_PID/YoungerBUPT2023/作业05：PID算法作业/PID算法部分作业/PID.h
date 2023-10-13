#ifndef __PID_H
#define __PID_H

typedef struct //�����ṹ�壬������PID��ÿһ������
{
	float target_value; //Ŀ��ֵ
	float actual_value; //ʵ��ֵ
	float err; //��ǰ���
	float err_last; //�ϴ�ƫ��
	float err_sum; //����ۼ�ֵ
	float Kp; //����ϵ��
	float Ki; //����ϵ��
	float Kd; //΢��ϵ��
}Pid;

void Pid_Init(void);

float P_realize(Pid* pid);

float PI_realize(Pid* pid);

float PID_realize(Pid* pid);

void PID_Set_Kp_Ki_Kd(float Kp, float Ki, float Kd);

void PID_Set_Actual_Target(float Actual, float Target);

Pid* Get_pid();

#endif