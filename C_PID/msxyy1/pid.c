#include "pid.h"
#include <stdio.h>

int main()
{   double ki,kp,kd,kf,set;
    PID pid1, pid2, pid3;
    PID_init(&pid1);
    PID_init(&pid2);
    PID_init(&pid3);
    printf("Enter the PID parameters to be used this time.\n");
    printf("ki: "); scanf("%lf",&ki);
    printf("kp: "); scanf("%lf",&kp);
    printf("kd: "); scanf("%lf",&kd);
    printf("kf: "); scanf("%lf",&kf);
    printf("target: "); scanf("%lf",&set);
    PID_SetParameter(&pid1,ki,kp,kd,kf,set);
    PID_SetParameter(&pid2,ki,kp,kd,kf,set);
    PID_SetParameter(&pid3,ki,kp,kd,kf,set);
    for(int i=0;i<100;i++){
        PID_PostionalPID(&pid1);
        if(i==0)printf("Postional\tIncremental\tFeedback\n");
        printf("%.2lf\t\t",pid1.error);
        PID_IncrementalPID(&pid2);
        printf("%.2lf\t\t",pid2.error);
        PID_IncrementalPID2(&pid3);
        printf("%.2lf\n",pid3.error);
    }
}