#include "PID.h" 
int PID_Initi(PID* pid) {
	pid->ki = 0;
	pid->kp = 0;
	pid->kd = 0;
	pid->previous_error = 0;
	pid->integral = 0;
	return 0;
}
int PID_SetParameters(PID* pid, double kp, double ki, double kd) {
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
	return 0;
}
double PID_PositionalPIDs(PID* pid, double setpoint, double current_value) {
	double error = setpoint - current_value;
	double output = pid->kp * error; return output;
}
double PID_IncrementalPIDs(PID* pid, double setpoint, double current_value) {
	double error = setpoint - current_value;
	double output = pid->kp * error + pid->ki * pid->integral + pid->kd * (error - pid->previous_error);
	pid->integral += error;
	pid->previous_error = error; return output;
}
