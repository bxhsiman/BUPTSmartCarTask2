#include "PID.h"
#include <stdlib.h>
//λ��ʽ 
db PID_PositionalPID(PID* pid,db now_pos){
	//���û��ַ�Χ 
	const db integral_max=20000;
	const db integral_min=-20000;
	//������� 
	pid->err=pid->target_pos-now_pos;
	//������֣��ۼӣ� 
	pid->integral+=pid->err;
	//��������߽������Ϊ�߽� 
	if(pid->integral>integral_max)
		pid->integral=integral_max;
	else if(pid->integral<integral_min)
		pid->integral=integral_min;
	db output=pid->kp*pid->err+
			  pid->ki*pid->integral+
			  pid->kd*(pid->err-pid->last_err1);
	//������һ����� 
	pid->last_err1=pid->err;
	return output;
}
//��ʼ���������趨����k���Լ�Ŀ��ֵ 
PID* PID_Init(db kp,db ki,db kd,db target_pos){
	//Ҫ�ü�ͷ���ݳ�Ա�Ļ���Ҫ�����ڴ� 
	PID* pid=(PID*)malloc(sizeof(PID));
	pid->kp=kp;
	pid->ki=ki;
	pid->kd=kd;
	pid->target_pos=target_pos;
	//����ָ�� 
	return pid;
}
//�޸Ĳ��� 
void PID_SetParameter(PID* pid,db kp,db ki,db kd){
	pid->kp=kp;
	pid->ki=ki;
	pid->kd=kd;
}
//����ʽ 
db PID_IncrementalPID(PID* pid,db now_pos){
	pid->err=pid->target_pos-now_pos;
	//�൱�ڰ�λ��ʽ�ı��ʽ�����˸��� 
	db output=pid->kp*(pid->err-pid->last_err1)+
			  pid->ki*pid->err+
			  pid->kd*(pid->err-2*pid->last_err1+pid->last_err2);
	//��Ҫά��ǰ������� 
	pid->last_err1=pid->err;
	pid->last_err2=pid->last_err1;
	return output;
}
