#include "PID.h"
#include <stdlib.h>
//位置式 
db PID_PositionalPID(PID* pid,db now_pos){
	//设置积分范围 
	const db integral_max=20000;
	const db integral_min=-20000;
	//计算误差 
	pid->err=pid->target_pos-now_pos;
	//计算积分（累加） 
	pid->integral+=pid->err;
	//如果超出边界就设置为边界 
	if(pid->integral>integral_max)
		pid->integral=integral_max;
	else if(pid->integral<integral_min)
		pid->integral=integral_min;
	db output=pid->kp*pid->err+
			  pid->ki*pid->integral+
			  pid->kd*(pid->err-pid->last_err1);
	//更新上一个误差 
	pid->last_err1=pid->err;
	return output;
}
//初始化，可以设定三个k，以及目标值 
PID* PID_Init(db kp,db ki,db kd,db target_pos){
	//要用箭头操纵成员的话就要申请内存 
	PID* pid=(PID*)malloc(sizeof(PID));
	pid->kp=kp;
	pid->ki=ki;
	pid->kd=kd;
	pid->target_pos=target_pos;
	//返回指针 
	return pid;
}
//修改参数 
void PID_SetParameter(PID* pid,db kp,db ki,db kd){
	pid->kp=kp;
	pid->ki=ki;
	pid->kd=kd;
}
//增量式 
db PID_IncrementalPID(PID* pid,db now_pos){
	pid->err=pid->target_pos-now_pos;
	//相当于把位置式的表达式都做了个差 
	db output=pid->kp*(pid->err-pid->last_err1)+
			  pid->ki*pid->err+
			  pid->kd*(pid->err-2*pid->last_err1+pid->last_err2);
	//需要维护前两个误差 
	pid->last_err1=pid->err;
	pid->last_err2=pid->last_err1;
	return output;
}
