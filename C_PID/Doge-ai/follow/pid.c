#include "pid.h"
#include <math.h>

/*************************************************************************
 *  函数名称：PID_Init
 *  功能说明：PID初始化
 *  参数说明：pid: PID结构体指针
 *  函数返回：0
 *************************************************************************/
int PID_Init(PID *pid) {
    pid->kp = 1;
    pid->ki = 0;
    pid->kd = 0;
    pid->p_out = 0;
    pid->i_out = 0;
    pid->d_out = 0;
    pid->output = 0;
    pid->target = 0;
    pid->current = 0;
    pid->error = 0;
    pid->last_error = 0;
    pid->pre_last_error = 0;
    pid->i_band = 1000;
    pid->max_integral = 1000;
    pid->max_output = 1000;
    return 0;
}

/*************************************************************************
 *  函数名称：PID_SetParameter
 *  功能说明：PID参数设置
 *  参数说明：pid: PID结构体指针
 *            kp: 比例系数
 *            ki: 积分系数
 *            kd: 微分系数
 *  函数返回：0
 *************************************************************************/
int PID_SetParameter(PID *pid, float kp, float ki, float kd) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    return 0;
}

/*************************************************************************
 *  函数名称：PID_PostionalPID
 *  功能说明：位置式PID计算
 *  参数说明：pid: PID结构体指针
 *  函数返回：0
 *************************************************************************/
int PID_PostionalPID(PID *pid) {
    pid->error = pid->target - pid->current;
    pid->p_out = pid->kp * pid->error;
    // 积分分离
    if(fabs(pid->current) <= pid->i_band){
        pid->i_out += pid->ki * pid->error;
        // 积分限幅
        LIMIT(pid->i_out, pid->max_integral);
    }
    else pid->i_out = 0;
    pid->d_out = pid->kd * (pid->error - pid->last_error);
    pid->output = pid->p_out + pid->i_out + pid->d_out;
    // 输出限幅
    LIMIT(pid->output, pid->max_output);
    pid->last_error = pid->error;
    return 0;
}

/*************************************************************************
 *  函数名称：PID_IncrementalPID
 *  功能说明：普通增量式PID计算
 *  参数说明：pid: PID结构体指针
 *  函数返回：0
 *************************************************************************/
int PID_IncrementalPID(PID *pid){
    pid->error = pid->target - pid->current;
    pid->p_out = pid->kp * (pid->error - pid->last_error);
    // 积分分离
    if(fabs(pid->current) <= pid->i_band){
        pid->i_out = pid->ki * pid->error;
        // 积分限幅
        LIMIT(pid->i_out, pid->max_integral);
    }
    else pid->i_out = 0;
    pid->d_out = pid->kd * (pid->error - 2 * pid->last_error + pid->pre_last_error);
    pid->output = pid->p_out + pid->i_out + pid->d_out;
    // 输出限幅
    LIMIT(pid->output, pid->max_output);
    pid->pre_last_error = pid->last_error;
    pid->last_error = pid->error;
    return 0;
}

/*************************************************************************
 *  函数名称：FeedForward
 *  功能说明：根据目标与预测模型前馈控制
 *  参数说明：target: 目标值
 *  函数返回：前馈输出值
 *************************************************************************/
float FeedForward(float target)
{
    //这里简单预测为线性模型
    float kf = 0.5;
    return kf * target;
}
