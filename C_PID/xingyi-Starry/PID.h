typedef struct
{
    float kp; // 比例系数
    float ki; // 积分系数
    float kd; // 微分系数
    float err; // 当前误差
    float last_err; // 上次误差
    float llast_err; // 上上次误差
    float max_err; // 误差上限
    float sum_err; // 累计误差
    float output; // 输出
} PID;

// 函数声明
int PID_Init(PID *pid,float target); // 初始化PID 
int PID_SetParameters(PID *pid, float kp, float ki, float kd, float max_err); // 设置PID参数
int PID_PostionalPID(PID *pid); // 位置式PID实现
int PID_IncrementalPID(PID *pid); // 增量式PID实现
float LimitMax(float input,float max); // 限幅函数