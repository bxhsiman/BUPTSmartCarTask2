#ifndef PID_H
#define PID_H

// 定义PID控制器结构体
typedef struct {
    double kp;          // 比例增益
    double ki;          // 积分增益
    double kd;          // 微分增益
    double proportional;// 比例项
    double kf;          // 前馈项
    double integral;    // 积分项
    double derivative;  // 微分项
    double error;       // 误差
    double prev_error;  // 上一次误差
    double prev2_error; // 上两次误差
    double set;         // 期望
    double current;     // 当前位置
    double output;      // 输出(控制量的值/控制量增量)
    double error_increment;     // 误差增量
    double control_increment;   // 控制量
    
} PID;

// 初始化PID变量
void PID_init(PID *pid) {
    pid->kp = 0.0;
    pid->ki = 0.0;
    pid->kd = 0.0;
    pid->kf = 0.0;
    pid->proportional = 0.0;
    pid->integral = 0.0;
    pid->derivative = 0.0;
    pid->error = 0.0;
    pid->prev_error = 0.0;
    pid->prev2_error = 0.0;
    pid->set = 0.0;
    pid->current = 0.0;
    pid->output = 0.0;
    pid->error_increment = 0.0;
    pid->control_increment = 0.0;
}

// 设置PID参数
void PID_SetParameter(PID *pid, double kp, double ki, double kd, double kf, double set) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->kf = kf;
    pid->set = set;
}

// 位置式PID实现
void PID_PostionalPID(PID *pid) {  
    pid->error = pid->set - pid->current;
    pid->proportional = pid->error;
    pid->integral += pid->error; 
    pid->derivative = pid->error - pid->prev_error;
    pid->prev_error = pid->error;
    pid->output = (pid->kp * pid->proportional) + (pid->ki * pid->integral) + (pid->kd * pid->derivative);      
    pid->current += pid->output;
}

// 增量式PID实现
void PID_IncrementalPID(PID *pid) {  
    pid->error = pid->set - pid->current;
    pid->proportional = pid->error - pid->prev_error;
    pid->integral = pid->error; 
    pid->derivative = pid->error - 2 * pid->prev_error + pid->prev2_error; 
    pid->prev2_error = pid->prev_error;        
    pid->prev_error = pid->error;
    pid->output = (pid->kp * pid->proportional) + (pid->ki * pid->integral) + (pid->kd * pid->derivative);       
    pid->control_increment += pid->output;  
    pid->current += pid->control_increment;           
}    

// 增加一个前馈项
void PID_IncrementalPID2(PID *pid) {  
    pid->error = pid->set - pid->current;
    pid->proportional = pid->error - pid->prev_error;
    pid->integral = pid->error; 
    pid->derivative = pid->error - 2 * pid->prev_error + pid->prev2_error; 
    pid->prev2_error = pid->prev_error;        
    pid->prev_error = pid->error;
    pid->output = (pid->kp * pid->proportional) + (pid->ki * pid->integral) + (pid->kd * pid->derivative) + (pid->kf * pid->set);       
    pid->control_increment += pid->output;  
    pid->current += pid->control_increment;           
} 
#endif