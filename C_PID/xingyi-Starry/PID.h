typedef struct
{
    float kp; // 比例系数
    float ki; // 积分系数
    float kd; // 微分系数
    float err;
    float sum_err;
    float last_err;
    float max_err;
} PID;

// 函数声明
int PID_Init(PID *pid,float target); // 初始化PID 
int PID_SetParameters(PID *pid, float kp, float ki, float kd, float max_err); // 设置PID参数
int PID_PostionalPID(PID *pid); // 位置式PID实现
int PID_IncrementalPID(PID *pp, float target, float measure, float *output, float *error); // 增量式PID实现