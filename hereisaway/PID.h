#ifndef _PID_H_

#define _PID_H_
#define db double

typedef struct{
	db kp;
	db ki;
	db kd;
	db integral;
	db err;
	db last_err1;
	db target_pos;
	db last_err2;
}PID;

db PID_PositionalPID(PID* pid,db now_pos);

PID* PID_Init(db kp,db ki,db kd,db target_pos);

void PID_SetParameter(PID* pid,db kp,db ki,db kd);

db PID_IncrementalPID(PID* pid,db now_pos);
#endif

