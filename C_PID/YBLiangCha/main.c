#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "pid.h"
//无法运行就把main函数剪切到pid.c中
int main(){
    const float Min = 0.0001;
    PID pid;
    float Kp,Ki,Kd;
    pid.MaxError = 300;    
    //初始化
    PID_Init(&pid);
    //参数设置
    printf("请输入Kp的值：");
    scanf("%f",&Kp);
    printf("\n");
    printf("请输入Ki的值：");
    scanf("%f",&Ki);
    printf("\n");
    printf("请输入Kd的值：");
    scanf("%f",&Kd);
    printf("\n");
    PID_SetParameter(&pid,Kp,Ki,Kd);
    //位置式PID实现
    pid.ActualValue = 0;
    pid.TargetValue = 100;
   do{
     PID_PositionalPID(&pid);
     printf("E1 = %f\n",pid.Error);
   }while(pid.Error > Min || pid.Error < -Min);
    

    //增量式PID实现
    pid.ActualValue = 0;
    pid.TargetValue = 100;
    do{
    PID_IncrementalPID(&pid);
    printf("E2 = %f\n",pid.Error);
    }while(pid.Error > Min || pid.Error < -Min);
    return 0 ;
    system("pause");
}
