#include<iostream>
using namespace std;
typedef struct {
	float kp;
	float ki;
	float kd;
	float target;
	float actual;
	float err;
	float last_err;
	float dt;
	float i;
	float result;
	float ll_err;
}PID;
typedef struct {
	float r_in;
	float last_Rin;
	float perr_Rin;

}F;
int PID_Init(PID *pid);            //初始化PID结构体
 int PID_SetParameter(float p, float i, float d, PID* pid);     //设置PID参数
 int PID_PostionalPID(float set, PID* pid);    //位置式PID实现
 int PID_IncrementalPID(float set, PID* pid);    //增量式PID实现
