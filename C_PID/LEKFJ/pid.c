#include <iostream>
#include"pid.h"
using namespace std;
int PID_Init(PID *pid) {
	pid->actual = 0.0;
	pid-> err = 0.0;
	pid->last_err = 0.0;
	pid->kp = 0.0;
	pid->ki = 0.0;
	pid->kd = 0.0;
	pid->i = 0.0;
	pid->ll_err = 0.0;
	pid->result = 0.0;
	pid->target = 0.0;
	return 0;
}

int PID_SetParameter(float p,float i,float d,PID *pid) {
	pid->kp = p;
	pid->ki = i;
	pid->kd = d;
	return 0;
}
int PID_PostionalPID(float set,PID *pid ) {
	pid->target = set;
	pid->err = pid->target - pid->actual;
	pid->i += pid->err;
	pid->result=pid->kp* pid->err + pid->ki * pid->i + pid->kd * (pid->err - pid->last_err);
	pid->last_err = pid->err;
	return (int)pid->result;

}
int PID_IncrementalPID(float set,PID *pid) {
	pid->target = set;
	pid->err = pid->target - pid->actual;
	float delt = pid->kp * (pid->err - pid->last_err) + pid->ki * pid->err + pid->kd * (pid->err - 2 * pid->last_err + pid->ll_err);
	pid->ll_err = pid->last_err;
	pid->last_err = pid->err;
	pid->result += delt;
	return (int)pid->result;
}
int main()
{
    F f;
    PID pid1, pid2, pid3;
    PID_Init(&pid1);
    PID_Init(&pid2);

    cout << "请输入本次使用的PID参数：\n";
    float p, i, d;
   
    cout << "KP:"; cin >> p; cout << endl;
    cout << "KI:"; cin >> i; cout << endl;
    cout << "KD:"; cin >> d; cout << endl;
    PID_SetParameter(p, i, d, &pid1);
    PID_SetParameter(p, i, d, &pid2);
    cout << "普通位置式pid  "; cout << "普通增量式pid \n ";
    cout << "误差表:\n";
    for (int i = 0; i < 20; i++) {
       pid1.actual+= PID_PostionalPID(100.0, &pid1);
       pid2.actual += PID_IncrementalPID(100.0, &pid2);
       cout << pid1.err << "  " << pid2.err << endl;
  

    
    }
}





