#include<stdio.h>
#include "PID.h"

/*设置PID参数*/
PID PID_SetParameter(PID s,double p, double i, double d)
{
    s.kd=d;
	s.ki=i;
	s.kp=p;
	return s;
}

/*位置式PID实现*/
ERROR PID_PostionalPID(PID s,ERROR e, double measure, double point)     
{
    e.error = measure - point;
    if(e.errorsum<10000&&e.errorsum>-10000)
        e.errorsum+= e.error;//对累计误差限制最大值
    double derror = e.error - e.lastError;
    e.preError = e.lastError;//对于下次运算而言，下次误差为下下次误差
    e.lastError = e.error;//对于下次运算而言，当前误差即为上次误差

    e.reli = s.kp*e.error + s.ki*e.errorsum + s.kd*derror;
    if(e.reli<100&&e.reli>-100)
		return e;//对输出进行限制
	else
		{
			if(e.reli>100) e.reli=100;
			else e.reli=-100;
			return e;
		}
}

/*增量式PID实现*/
ERROR PID_IncrementalPID(PID s,ERROR e, double measure, double point)    
{
    e.error = measure - point;

    double derror = e.error - e.lastError;
    double dderror = e.error - 2*e.lastError + e.preError;
    e.preError = e.lastError;//对于下次运算而言，下次误差为下下次误差
    e.lastError = e.error;//对于下次运算而言，当前误差即为上次误差

	e.reli = s.kp*derror + s.ki*e.error + s.kd*dderror;
	if(e.reli<100&&e.reli>-100)
			return e;//对输出进行限制
	else
		{
			if(e.reli>100) e.reli=100;
			else e.reli=-100;
			return e;
		}
}
