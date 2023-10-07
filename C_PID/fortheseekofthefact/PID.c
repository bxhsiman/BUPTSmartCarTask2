#include"PID.h"
#include<stdio.h>
#include<stdlib.h>
void PPID_Init(PPID* ppid){     //init
	ppid->setspeed=0.0;
	ppid->actualspeed=0.0;
	ppid->err=0.0;
	ppid->err_last=0.0;
	ppid->kd=0.0;
	ppid->ki=0.0;
	ppid->kp=0.0;
	ppid->voltage=0.0;
	ppid->jifen=0.0;
}
float PPID_SetParameter(PPID* ppid){
	ppid->kd=0.2;
	ppid->ki=0.015;
	ppid->kp=0.2;
}
float PID_PostionalPID(float speed,PPID* ppid){
	ppid->setspeed=speed;
	ppid->err=ppid->setspeed-ppid->actualspeed;
	ppid->jifen+=ppid->err;
	ppid->voltage=ppid->kp*ppid->err+ppid->ki*ppid->jifen+ppid->kd*(ppid->err-ppid->err_last);
	ppid->err_last=ppid->err;
	ppid->actualspeed=ppid->voltage;
	return ppid->actualspeed;
}
//I
void IPID_Init(IPID* ipid){
	ipid->actualspeed=0.0;
	ipid->setspeed=0.0;
	ipid->err=0.0;
	ipid->err_last=0.0;
	ipid->err_last_last=0.0;
	ipid->kp=0.0;
	ipid->ki=0.0;
	ipid->kd=0.0;
}
float IPID_SetParameter(IPID* ipid){
	ipid->kd=0.2;
	ipid->ki=0.01;
	ipid->kp=0.2;
}
float PID_IncrementalPID(float speed,IPID* ipid){
	float increase;
	ipid->setspeed=speed;
	ipid->err=ipid->setspeed-ipid->actualspeed;
	increase=ipid->kp*(ipid->err-ipid->err_last_last)+ipid->ki *ipid->err+ipid->kd*(ipid->err-2*ipid->err_last+ipid->err_last_last);
	ipid->actualspeed+=increase;
	ipid->err_last_last=ipid->err_last;
	ipid->err_last=ipid->err;
	return ipid->actualspeed;
}