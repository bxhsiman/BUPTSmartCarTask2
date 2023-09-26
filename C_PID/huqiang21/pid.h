#ifndef _PID.C_H
#define _PID>C_H
#endif

typedef struct
{
    float kp;
    float ki;
    float kd;
    float err;                //误差
    float target;             //目标值
    float last_err;           //上一次误差
    float sum;                //误差之和
    float pos_result;         //位置式pid计算的变化量
    float err_diff;           //两次误差之差
    float prior_err;          //前两次误差
    float delt_inc_result;
    float inc_result;         //增量式pid计算的变化量
    float d;                  //增量式PID的kd系数
    float actual;             //目前的量
}PID;

int PID_Init(PID*pid);
int PID_SetParameter(float p, float i, float d, PID*pid);
float PID_PostionalPID(float target, float actual, PID*pid);
float PID_IncrementalPID(float target, float actual, PID*pid);