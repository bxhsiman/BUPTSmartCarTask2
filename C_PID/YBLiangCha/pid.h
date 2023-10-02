
/*你需要实现以下函数：
``` c
    //PID.h
    int PID_Init(...);             //初始化PID结构体
    int PID_SetParameter(...);      //设置PID参数
    int PID_PostionalPID(...);      //位置式PID实现
    int PID_IncrementalPID(...);    //增量式PID实现
```*/
#include <stdio.h>
typedef struct {
    float Kp;
    float Ki;
    float Kd;
    float Error;
    float MaxError;//积分限幅
    float LastError0;//上次误差
    float SumError;
    float ErrorDifference;
    float Result;
    //增量式PID所需的变量
    float LastError1;//上上次误差
    float Speed;
    float Delta;
    float Output;
    float TargetValue;
    float ActualValue;
}PID;

//函数声明
int PID_Init(PID *pid);
int PID_SetParameter(PID*pid,float Kp,float Ki,float Kd);
float PID_PositionalPID(PID*pid);
float PID_IncrementalPID(PID*pid);
