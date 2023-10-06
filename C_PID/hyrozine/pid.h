#ifndef _PID_H

#define fl float  
#define _PID_H

struct PID
{
	fl kp;
	fl ki;
	fl kd;
	fl integral;            //误差和
	fl err;                 //本次误差
	fl last_err;            //上一次误差
	fl front_err;           //前一次误差
	fl target;              //目标位置
	fl pwm;                 //输出
}pid1, pid2;

void PID_Init(struct PID* pid);                                               //初始化PID结构体
int PID_SetParameter(struct PID* pid, fl kp, fl ki, fl kd,fl target);         //设置PID参数
float PID_PostionalPID(struct PID* pid, fl target);                           //位置式PID实现
float PID_IncrementalPID(struct PID* pid, fl target);                         //增量式PID实现


#endif
