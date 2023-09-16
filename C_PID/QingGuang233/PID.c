#include "PID.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "windows.h"

int PID_Init(PID *pid){
    pid->kp = 0;
    pid->ki = 0;
    pid->kd = 0;
    pid->kf = 0;
    pid->target = 0;
    pid->last_target = 0;
    pid->pos = 0;
    pid->last_err = 0;
    pid->integral = 0;
    return 0;
}

int PID_SetParameter(float kp,float ki,float kd,float kf,PID* pid){
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->kf = kf;
    return 0;
}

int PID_SetTarget(float target,PID* pid){
    pid->last_target = pid->target;
    pid->target = target;
    return 0;
}

float PID_PositionalPID(PID* pid){
    float err = pid->target - pid->pos;
    pid->integral += err;
    float p = pid->kp * err;
    float i = pid->ki * pid->integral;
    float d = pid->kd * (err - pid->last_err);
    return pid->pos += (p + i + d);
}

float PID_IncrementalPID(PID* pid){
    float err = pid->target - pid->pos;
    pid->integral += err;
    float p = pid->kp * err;
    float i = pid->ki * pid->integral;
    float d = pid->kd * (err - pid->last_err);
    float increment = p + i + d;
    pid->pos += increment;
    return increment;
}

float PID_FeedforwardIncrementalPID(PID* pid){
    float err = pid->target - pid->pos;
    pid->integral += err;
    float p = pid->kp * err;
    float i = pid->ki * pid->integral;
    float d = pid->kd * (err - pid->last_err);
    float f = pid->kf * (pid->target - pid-> last_target);
    float increment = p + i + d + f;
    pid->pos += increment;
    return increment;
}

int main(){
    PID pid;
    PID_Init(&pid);
    PID_SetParameter(0.1,0.1,0.1,0.01,&pid);
    int i = 10;
    while(1){
        if(i >= 9){
            srand((unsigned int)time(NULL));
            i = 0;
            PID_SetTarget(rand()%200-100,&pid);
        }
        PID_FeedforwardIncrementalPID(&pid);
        printf("当前位置:%f,目标位置:%f\n",pid.pos,pid.target);
        Sleep(100);
        i++;
    }
}