#ifndef _PID_H_

#define fl float  
#define _PID_H_

typedef struct 
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
}PID;
void PID_Init(PID* pid);                                               //初始化PID结构体
int PID_SetParameter(PID* pid, fl kp, fl ki, fl kd,fl target);      //设置PID参数
float PID_PostionalPID(PID* pid, fl target);                           //位置式PID实现
float PID_IncrementalPID(PID* pid, fl target);                         //增量式PID实现
#endif
