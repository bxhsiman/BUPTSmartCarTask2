// 使用c语言实现位置式和增量式PID控制器

// 单独将结构体和相关函数的声明放到PID.h

// 结构体声明
typedef struct
{
    float kp; // 比例系数
    float ki; // 积分系数
    float kd; // 微分系数
    float maxError; // 误差上限
    float maxSumError; // 积分上限
    float lastError; // 上一次误差
    float sumError; // 误差累计
    float lastLastError; // 上上次误差
} PID;

// 函数声明
void PID_Init(PID *pp, float kp, float ki, float kd, float maxError, float maxSumError); // 初始化PID 
int PID_SetParameters(PID *pp, float kp, float ki, float kd, float maxError, float maxSumError); // 设置PID参数
int PID_PostionalPID(PID *pp, float target, float measure, float *output, float *error); // 位置式PID实现
int PID_IncrementalPID(PID *pp, float target, float measure, float *output, float *error); // 增量式PID实现
