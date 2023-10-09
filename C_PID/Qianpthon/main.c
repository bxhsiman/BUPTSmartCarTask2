#include "pid.c"
#include "pid.h"
#include "stdio.h"
int main(){
    //pid初始化
    PID pid1;
    PID pid2;
    PID_Init(&pid1);
    PID_Init(&pid2);

    //设置pid参数
    float kp=1;
    float ki=0.1;
    float kd=0.1;
    float ilimit=1000;
    float outlimit=1000;
    printf("input pid parameter:\n");
    printf("kp:");
    scanf("%f",&kp);
    printf("ki:");
    scanf("%f",&ki);
    printf("kd:");
    scanf("%f",&kd);
    PID_SetParameter(kp,ki,kd,ilimit,outlimit,&pid1);
    PID_SetParameter(kp,ki,kd,ilimit,outlimit,&pid2);
    float tar=100;
    float pos1=0;//位置式pid
    float pos2=0;//增量式pid
    
    //pid计算
    printf("位置式pid:   增量式pid:\n");
    for(int i=0;i<100;i++){
        
        PID_PostionalPID(&pid1,tar,pos1);
        PID_IncrementalPID(&pid2,tar,pos2);
        pos1+=pid1.out;
        pos2+=pid2.out;
        printf("E:%f",pid1.ek);
        printf("E:%f\n",pid2.ek);

    }
    return 0;
}