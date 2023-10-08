typedef struct
{
    float                kp;         //P
    float                ki;         //I
    float                kd;         //D
    float                imax;       //积分限幅

    float                out_p;  //KP输出
    float                out_i;  //KI输出
    float                out_d;  //KD输出
    float                out;    //pid输出

    float                target;//目标值
    float                integrator; //< 积分值
    float                last_error; //< 上次误差
    float                pre_error; //<上上次误差
    float                last_derivative;//< 上次误差与上上次误差之差
    unsigned long        last_t;     //< 上次时间

    float                fcc_a; //前馈参数1
    float                fcc_b; //前馈参数2
}PID_t;

void PID_Init(PID_t*pid);             //初始化PID结构体
void PID_SetParameter(PID_t*pid);      //设置PID参数
float PID_PostionalPID(PID_t*pid,float error);      //位置式PID实现
float PID_IncrementalPID(PID_t*pid,float error);    //增量式PID实现
float PID_FeedForwardPID(PID_t*pid,float error);  //前馈式pid实现
