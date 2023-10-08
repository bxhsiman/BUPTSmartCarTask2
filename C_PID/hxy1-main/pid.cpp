#include <iostream>
#include"pid.h"
using namespace std;

// Initialize PID Controller
void PID_Init(PIDController* pid) {
    pid->setpoint = 0.0;
    pid->kp = 0.0;
    pid->ki = 0.0;
    pid->kd = 0.0;
    pid->prev_error = 0.0;
    pid->integral = 0.0;
    pid->prev_control = 0.0;
}

// Set PID Parameters
void PID_SetParameter(PIDController* pid, float kp, float ki, float kd) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
}

// Positional PID Implementation
float PID_PostionalPID(PIDController* pid, float pv) {
    float error = pid->setpoint - pv;
    pid->integral += error;
    float derivative = error - pid->prev_error;
    pid->prev_error = error;
    return pid->kp * error + pid->ki * pid->integral + pid->kd * derivative;
}

// Incremental PID Implementation
float PID_IncrementalPID(PIDController* pid, float pv) {
    float error = pid->setpoint - pv;
    float incremental_control = pid->kp * (error - pid->prev_error) + pid->ki * error + pid->kd * (error - 2 * pid->prev_error + pid->prev_control);
    pid->prev_control = pid->prev_error;
    pid->prev_error = error;
    return incremental_control;
}

int main()
{
    PIDController pid1, pid2, pid3;
    PID_Init(&pid1);
    PID_Init(&pid2);
    cout << "请输入本次使用的PID参数：\n";
    float p, i, d;

    cout << "KP:"; cin >> p; cout << endl;
    cout << "KI:"; cin >> i; cout << endl;
    cout << "KD:"; cin >> d; cout << endl;
    PID_SetParameter(&pid1, p, i, d);
    PID_SetParameter(&pid2, p, i, d);
    cout << "普通位置式pid  "; cout << "普通增量式pid \n ";
    cout << "误差表:\n";
    for (int i = 0; i < 23; i++) {
        pid1.setpoint -= PID_PostionalPID(&pid1, -100.0);
        pid2.setpoint -= PID_IncrementalPID(&pid2, -100.0);
        cout << pid1.prev_error << "  " << pid2.prev_error << endl;
    }
}

