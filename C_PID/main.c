#include <stdio.h>
#include "PID.h"

int main()
{
    //用于PID参数设置
    PID* pid_set_point;
    PID pid_set;
    pid_set_point = &pid_set;

    //用于接受pid函数返回值
    float u_p = 0;
    float u_i = 0;

    //用于显示error变化
    float error_print_p = 0;
    float error_print_i = 0;
    
    //输入pid值
    printf("输入P：");
    scanf_s("%f", &pid_set.kp);

    printf("输入I：");
    scanf_s("%f", &pid_set.ki);
    
    printf("输入D：");
    scanf_s("%f", &pid_set.kd);
   
    //初始化
    PID_Init();
    ERROR_Init();

    PID_SetParameter(pid_set_point);

    printf("位置式PID：                增量式PID：\n");
    while (1)
    {
        //获取error
        error_get_p();
        error_get_i();
        
        //获取移动量
        u_p = PID_PostionalPID();
        u_i = PID_IncrementalPID();

        //移动
        error_print_p = move_p(u_i);
        error_print_i = move_i(u_p);
        
        //显示error变化
        printf("%f                         %f \n", error_print_p,error_print_i);
        
        system("pause");//停一下，要不然翻太快了
    }
    return 0;
}