#include <stdio.h>

// 定义PID控制器结构体
typedef struct {
    float kp;  // 比例系数
    float ki;  // 积分系数
    float kd;  // 微分系数
    float setpoint;  // 目标值
    float error_sum;  // 误差累计值
    float last_error;  // 上一次误差值
} PIDController;

// 初始化PID控制器
void PIDController_init(PIDController* pid, float Kp, float Ki, float Kd, float setpoint) {
    pid->kp = Kp;
    pid->ki = Ki;
    pid->kd = Kd;
    pid->setpoint = setpoint;
    pid->error_sum = 0;
    pid->last_error = 0;
}

// 计算PID控制器输出
float PIDController_compute(PIDController* pid, float input, float dt) {
    // 计算误差
    float error = pid->setpoint - input;

    // 计算误差累计值
    pid->error_sum += error * dt;

    // 计算误差变化率
    float error_delta = (error - pid->last_error) / dt;

    // 计算PID控制器输出
    float output = pid->kp * error + pid->ki * pid->error_sum + pid->kd * error_delta;

    // 保存上一次误差值
    pid->last_error = error;

    return output;
}

int main() {
    // 用户输入PID参数
    float kp, ki, kd;
    printf("请输入kp: ");
    scanf("%f", &kp);
    printf("请输入ki: ");
    scanf("%f", &ki);
    printf("请输入kd: ");
    scanf("%f", &kd);

    // 初始化PID控制器
    PIDController position_pid, incremental_pid, feedforward_pid;
    PIDController_init(&position_pid, kp, ki, kd, 10.0);
    PIDController_init(&incremental_pid, kp, ki, kd, 10.0);
    PIDController_init(&feedforward_pid, kp, ki, kd, 10.0);

    // 模拟系统
    float input = 0;
    float dt = 0.01;
    printf("时间 (s)\t位置式误差\t增量式误差\t前馈增量式误差\n");
    for (int i = 0; i < 1000; i++) {
        // 计算PID控制器输出
        float position_output = PIDController_compute(&position_pid, input, dt);
        float incremental_output = PIDController_compute(&incremental_pid, input, dt);
        float feedforward_output = PIDController_compute(&feedforward_pid, input, dt);

        // 计算模拟系统响应
        input += position_output * dt;

        // 计算误差
        float position_error = position_pid.setpoint - input;
        float incremental_error = incremental_pid.setpoint - input;
        float feedforward_error = feedforward_pid.setpoint - input;

        // 打印误差
        printf("%f\t%f\t%f\t%f\n", i * dt, position_error, incremental_error, feedforward_error);
    }

    return 0;
}
