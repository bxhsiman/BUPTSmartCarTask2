#ifndef PID_H       
#define PID_H       

typedef struct {
    float kp;       // 比例系数
    float ki;       // 积分系数
    float kd;       // 微分系数
    float maxI;     // 积分限幅
    float maxOut;   // 输出限幅
    float lastError;// 上次误差
    float integral; // 积分项
    float output;   // 输出值
    float prevError;// 上上次误差
} PID;


int PID_Init(PID *pid);             // 初始化PID
int PID_SetParameter(PID *pid, float kp, float ki, float kd, float maxI, float maxOut);     // 设置PID参数
int PID_PostionalPID(PID *pid, float reference, float feedback);                            // 位置式PID
int PID_IncrementalPID(PID *pid, float reference, float feedback);                          // 增量式PID

#endif           