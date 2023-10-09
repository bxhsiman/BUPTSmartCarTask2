#include "PID.h"

int PID_Init(PID *pid) {        // 初始化pid参数
    pid->kp = 0;   // 比例系数
    pid->ki = 0;   // 积分系数
    pid->kd = 0;   // 微分系数
    pid->maxI = 0;   // 最大积分值
    pid->maxOut = 0;   // 最大输出值
    pid->lastError = 0; // 上一次误差
    pid->integral = 0;  // 积分值
    pid->output = 0;    // 输出值
    pid->prevError = 0; // 上上次误差
    return 0;
}

int PID_SetParameter(PID *pid, float kp, float ki, float kd, float maxI, float maxOut) {    // 设置pid参数
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->maxI = maxI;
    pid->maxOut = maxOut;
    return 0;
}

int PID_PostionalPID(PID *pid, float reference, float feedback) {   // 位置式pid
    float error = reference - feedback; // 误差
    float pOut = pid->kp * error;       // 比例项
    pid->integral += error;             
    if (pid->integral > pid->maxI) {            // 积分限幅
        pid->integral = pid->maxI;      
    } else if (pid->integral < -pid->maxI) {        
        pid->integral = -pid->maxI;     
    }
    float iOut = pid->ki * pid->integral;  // 积分项
    float dOut = pid->kd * (error - pid->lastError);    // 微分项
    pid->lastError = error;                 
    float output = pOut + iOut + dOut; // 输出值
    if (output > pid->maxOut) {                   // 输出限幅
        output = pid->maxOut;
    } else if (output < -pid->maxOut) {
        output = -pid->maxOut;
    }
    pid->output = output;
    return 0;
}

int PID_IncrementalPID(PID *pid, float reference, float feedback) {   // 增量式pid
    float error = reference - feedback;
    float pOut = pid->kp * (error - pid->lastError);            // 比例项
    pid->lastError = error;
    pid->integral += error;
    if (pid->integral > pid->maxI) {     // 积分限幅
        pid->integral = pid->maxI;
    } else if (pid->integral < -pid->maxI) {
        pid->integral = -pid->maxI;
    }
    float iOut = pid->ki * pid->integral;                         // 积分项                          
    float dOut = pid->kd * (error - 2 * pid->lastError + pid->prevError); // 微分项
    pid->prevError = pid->lastError;
    float output = pOut + iOut + dOut;  // 输出值
    if (output > pid->maxOut) {  // 输出限幅
        output = pid->maxOut;
    } else if (output < -pid->maxOut) {
        output = -pid->maxOut;
    }
    pid->output = output;
    return 0;
}