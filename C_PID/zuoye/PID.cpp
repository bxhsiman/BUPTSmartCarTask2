#include "PID.h"
using namespace std;
PID pid;
PID pid_1;
void initialization(PID *pid){//初始化
    /*pid_1.actual=0;
    pid_1.sum=0;
    pid_1.err=0;
    pid_1.err_last=0;
    pid_1.P=0.2;
    pid_1.I=0.015;
    pid_1.D=0.2;
    pid_1.update=0;

    pid.actual=0;
    pid.sum=0;
    pid.err=0,pid.err_last=0,pid.err_next=0;
    pid.P=0.2;
    pid.I=0.015;
    pid.D=0.2;
    pid.update=0;*/

    pid->actual=0;
    pid->err=set;
    pid->err=0;
    pid->err_last=0;
    pid->err_next=0;
    pid->sum=0;
}
void PID_position(PID *pid){
    /*pid_1.err=set-pid_1.actual;
    pid_1.sum+=pid_1.err;
    pid_1.update=pid_1.P*pid_1.err+pid_1.I*pid_1.sum+pid_1.D*(pid_1.err-pid_1.err_last);
    pid_1.actual+=pid_1.update;
    pid_1.err_last=pid_1.err;*/

    pid->err=set-pid->actual;
    pid->update=P*pid->err+I*pid->sum+D*(pid->err-pid->err_last);
    pid->actual+=pid->update;
    pid->err_last=pid->err;
    pid->sum+=pid->err;
}
void PID_add(PID *pid){
    /*pid.err=set-pid.actual;
    pid.update+=(pid.P*(pid.err-pid.err_last)+pid.I*pid.err+pid.D*(pid.err-2*pid.err_last+pid.err_next));
    pid.actual+=pid.update;
    pid.err_last=pid.err;
    pid.err_next=pid.err_last;*/

    pid->err=set-pid->actual;
    pid->update+=(P*(pid->err-pid->err_last)+I*pid->err+D*(pid->err-2*pid->err_last+pid->err_next));
    pid->actual+=pid->update;
    pid->err_last=pid->err;
    pid->err_next=pid->err_last;
}