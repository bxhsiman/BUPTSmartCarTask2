#ifndef PID_H
#define PID_H//多次用
#define LIMIT(TargetValue, LimitValue) \
if (TargetValue > LimitValue)\
{\
  TargetValue = LimitValue;\
}\
else if (TargetValue < -LimitValue)\
{\
  TargetValue = -LimitValue;\
}//限幅

typedef struct {
    float kp;  // 比例系数
    float ki;  // 积分系数
    float kd;  // 微分系数
    float p_out;  // 比例输出
    float i_out;  // 积分输出
    float d_out;  // 微分输出
    float output;  // 输出值
    float target;  // 设定值
    float current;  // 当前值
    float error;  // 误差
    float last_error;  // 上一次的误差
    float pre_last_error;  // 上上次的误差
    float i_band;  // 积分分离值
    float max_integral; // 最大积分值
    float max_output; // 最大输出值
} PID;//各项数据封装为一个结构体

int PID_Init(PID *pid);//初始化
int PID_SetParameter(PID *pid, float kp, float ki, float kd);//设置参数
int PID_PostionalPID(PID *pid);//位置式PID计算
int PID_IncrementalPID(PID *pid);//增量式PID计算
float FeedForward(float target);//前馈式

#endif /* PID_H */
