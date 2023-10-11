#include "PID.c"
#include <stdio.h>

int main(void)
{
    float np1=100;
    float np2=100;
    
    PID_t PID1;
    PID_t PID2;
    PID_Init(&PID1);
    PID_SetParameter(&PID1);

    printf("请输入本次的PID参数\nkp:");
    scanf("%f",&PID1.kp);
    printf("ki:");
    scanf("%f",&PID1.ki);
    printf("kd:");
    scanf("%f",&PID1.kd);
    PID2=PID1;

    printf("普通位置式pid   普通增量式pid\n误差表：\n");
    int i=50;
    while(i)
    {
        printf("E:%.2f  E:%.2f  E:%.2f\n",np1,np2);
        np1=np1-PID_PostionalPID(&PID1,np1);
        np2=np2-PID_IncrementalPID(&PID2,np2);

        i--;
    }

    return 0;
}