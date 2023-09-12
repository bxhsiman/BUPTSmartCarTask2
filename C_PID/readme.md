# PID作业
使用**c语言**实现位置式和增量式PID控制器，要求如下：
1. 将PID控制器使用的变量封装为结构体。
2. 单独将结构体和相关函数的*声明*放到`PID.h`,将实现写在`PID.c`当中。
3. 单独创建一个`main.c`用来模拟执行你的PID控制器,注意结构体指针的使用
对于第一个任务*封装*的解释如下：
``` c
    typedef struct {
        float ki;
        float kp;
        ...
    } PID;
```
对于第二个任务没什么好解释的
对于第三个任务结构体指针的解释如下：
``` c
    PID * ...
    ... -> ??
```
你需要实现以下函数：
``` c
    //PID.h
    int PID_Init(...);             //初始化PID结构体
    int PID_SetParameter(...);      //设置PID参数
    int PID_PostionalPID(...);      //位置式PID实现
    int PID_IncrementalPID(...);    //增量式PID实现
```
运行示例如图：

<image src= ../assets/PID.png>

