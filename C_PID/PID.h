#ifndef PID_H 
#define PID_H 
typedef struct {
	double ki;
	double kp;
	double kd;
	double previous_error;
	double integral;
} PID;
int PID_Initi(PID* pid);
int PID_SetParameters(PID* pid,double kp, double ki, double kd);
double PID_PositionalPIDs(PID* pid, double setpoint, double current_value);
double PID_IncrementalPIDs(PID* pid, double setpoint, double current_value);
#endif 
