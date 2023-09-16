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

PID PID_SetParameter(PID s,double p, double i, double d);
ERROR PID_PostionalPID(PID s,ERROR e, double measure, double point);
ERROR PID_IncrementalPID(PID s,ERROR e, double measure, double point);