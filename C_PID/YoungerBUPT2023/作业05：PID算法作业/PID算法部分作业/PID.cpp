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

float P_realize(Pid* pid)
{
	pid->err = pid->target_value - pid->actual_value; //��ǰ���=Ŀ��ֵ-��ʵֵ
	pid->actual_value = pid->Kp * (pid->err); //ÿһ�ε��ú���ʱ����ʵ��ֵ�����޸�

	return pid->actual_value;
}

float PI_realize(Pid* pid)
{
	pid->err = pid->target_value - pid->actual_value; //��Ŀ��ֵ֮������
	pid->err_sum += pid->err; //�ۼ����
	pid->actual_value = pid->Kp * (pid->err) + pid->Ki * (pid->err_sum);
	return pid->actual_value;
}

float PID_realize(Pid* pid)
{
	pid->err = pid->target_value - pid->actual_value; //��ǰ���

	//����
	pid->err_sum += pid->err; //����ۼ�ֵ
	pid->actual_value = pid->Kp * (pid->err) + pid->Ki * (pid->err_sum)
		+ pid->Kd * (pid->err - pid->err_last);  //����+����+΢��

	pid->err_last = pid->err;

	return pid->actual_value;
}

void PID_Set_Kp_Ki_Kd(float Kp, float Ki, float Kd)
{
	Pid* ptr = &Motor1_PID_Contorl;
	ptr->Kd = Kd;
	ptr->Kp = Kp;
	ptr->Ki = Ki;
}

void PID_Set_Actual_Target(float Actual, float Target)
{
	Pid* ptr = &Motor1_PID_Contorl;
	ptr->actual_value = Actual;
	ptr->target_value = Target;
}

Pid* Get_pid()
{
	return &Motor1_PID_Contorl;
}
