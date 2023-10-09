
#ifndef PID_H
#define PID_H
#pragma once
//Positional
typedef struct PostionalPID{
	float setspeed;
	float actualspeed;
	float err;
	float err_last;
	float kp,ki,kd; //portion,jifen,weifenxishu
	float voltage;
	float jifen;
}PPID;
PPID* ppid;
void PPID_Init(PPID* ppid); //initialize
float PPID_SetParameter(PPID* ppid);
float PID_PostionalPID(float speed,PPID* ppid); 
//Incremental
typedef struct IncrementalPID{
	float setspeed;
	float actualspeed;
	float err;
	float err_last;
	float err_last_last;
	float kp,ki,kd; //portion,jifen,weifenxishu
}IPID;
IPID* ipid;
void IPID_Init(IPID* ipid);
float IPID_SetParameter(IPID* ipid);
float PID_IncrementalPID(float speed,IPID* ipid);

#endif