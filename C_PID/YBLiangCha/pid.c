#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include  "pid.h"


//初始化结构体

int PID_Init(PID *pid){

    pid->Kd = 0;
    pid->Ki = 0;
    pid->Kp = 0;
    pid->LastError0 = 0;
    pid->LastError1 = 0;
    pid->Output = 0;
    return 0 ;
}
//设置PID参数
int PID_SetParameter(PID*pid,float Kp,float Ki,float Kd){
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    
    return 0;
}

//位置式PID实现
float PID_PositionalPID(PID*pid){
    pid->Error = pid->TargetValue - pid->ActualValue;
    pid->SumError += pid->Error;
    //误差限幅
    if (pid->SumError > pid->MaxError){
        pid->SumError = pid->MaxError;
    }else if (pid->SumError < -pid->MaxError){
        pid->SumError = -pid->MaxError;
    }
    pid->ErrorDifference = pid->Error - pid->LastError0;
    pid->LastError0 = pid->Error;
    float Proportion = pid->Kp*pid->Error;
    float Integral = pid->Ki * pid->SumError;
    float Derivative = pid->Kd * pid->ErrorDifference;
    pid->Result = Proportion + Integral + Derivative;
    pid->ActualValue = pid->Result;
    return pid->Result;
}

//增量式PID实现

float PID_IncrementalPID(PID*pid){

    pid->Error = pid->TargetValue - pid->ActualValue;
    float Proportion = pid->Kp*(pid->Error - pid->LastError0);
    float Integral = pid->Ki * pid->Error;
    float Derivative = pid->Kd*(pid->Error + pid->LastError1 - 2*pid->LastError0);
    pid->Delta = Proportion + Integral + Derivative ;
    pid->Output += pid->Delta;
    pid->ActualValue = pid->Output;
    return pid->Output;
}

