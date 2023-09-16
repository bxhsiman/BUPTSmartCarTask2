#include<stdio.h>
#define m 0.5 //模拟车的质量0.5kg
#define ku 0.1//假设小车受到的空气阻力与速度成正比,比例系数0.1，即阻力（牛顿）=0.1*v
#define fu 1 //假设小车所受地面摩擦力为1N
typedef struct {
    double kp;
    double kd;
    double ki;
}PID;

typedef struct {
    double error;//当前误差
    double errorsum;//累计误差
    double lastError;//上次误差
    double preError;//上上次误差
    double reli; //每次运算反馈的值
}ERROR;

extern PID PID_SetParameter(PID s,double p, double i, double d);
extern ERROR PID_PostionalPID(PID s,ERROR e, double measure, double point);
extern ERROR PID_IncrementalPID(PID s,ERROR e, double measure, double point);
int main()
{

    double time = 0;//time表示时间，从零开始计时
    double t = 0.05;//t模拟每0.05秒进行一次误差的测量与对牵引力的调整
    double x1 =100, x2 = 100; //x模拟小车当前L离目标100m
    double v1 = 0, v2 = 0;  //v为小车初速度
    double F1 = 0, F2 = 0; //F为小车牵引力

    PID s1,s2; ERROR e1,e2;
    e1.error=e1.errorsum=e1.lastError=e1.preError=100;
    e2.error=e2.errorsum=e2.lastError=e2.preError=100;
    s1=PID_SetParameter(s1,1,0,32);
	s2=PID_SetParameter(s2,11,0.4,62);//初始化
	printf("位置式PID\t\t增量式PID\n");

    while(time<10){//模拟10秒后自动停止运行
        /*这里将每个0.05秒间隔内小车牵引力、位移及速度变化很小，取该时间段内的牵引力及速度视作恒定。*/
        v1 = ((F1-ku*v1)/m)*t + v1;  //即v2=a*dt+v1
        x1 = x1 - v1*t;               //由于时间间隔t很小，每一小段近似为匀速
        e1 = PID_PostionalPID(s1,e1,x1,0);
        F1 = 0.5*e1.reli;
        
        v2 = ((F2-ku*v2-fu)/m)*t + v2;
        x2 = x2 - v2*t;
        e2 = PID_IncrementalPID(s2,e2,x2,0);
        F2 = F2 + 0.5*e2.reli;
        
        time+=0.05;
        printf("ERROR:%f   \t\tERROR:%f\n",x1,x2);
    }

    return 0;
}