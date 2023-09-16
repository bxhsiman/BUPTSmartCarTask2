#include <iostream>
using namespace std;
float set,P,I,D;
typedef struct
{
    float actual;//实际值
    float sum;//积分值
    float err,err_last,err_next;//当前误差与上两次误差
    //float P,I,D;//比例，积分，微分比例
    float update;//修正量增量
}PID;
void PID_add(PID *pid);
void PID_position(PID *pid);
void initialization(PID *pid);