#include"pid.h"
#include "stdio.h"


int PID_Init(PID* pidtest1)
{
    pidtest1->ki = 0;
    pidtest1->kp = 0;
    pidtest1->kd = 0;
    pidtest1->Outputmax = 0;
    pidtest1->intergral = 0;
    pidtest1->lasterror=0;
    pidtest1->preverror=0;
    return 0;


}

float PID_SetParameter(PID* pidtest1,float I, float P, float D,float max)
{
    
    pidtest1->ki = I;
    pidtest1->kp = P;
    pidtest1->kd = D;//设置PID算法的三个控制参数
    pidtest1->Outputmax = max;
    return 0;
}

float PID_PostionalPID(PID*pidtest1)//位置式pid
{
    float output, iError;
    iError = pidtest1->Aimposit - pidtest1->Nowposit;
    output = pidtest1->kp * iError + pidtest1->kd * (iError - pidtest1->lasterror);//p部分和d部分之和
  pidtest1->intergral += pidtest1->ki * iError;	            //位置式PID积分项累加
     pidtest1->intergral=pidtest1->intergralmax<pidtest1->intergral? pidtest1->intergralmax: pidtest1->intergral;
     pidtest1->intergral= -pidtest1->intergralmax>pidtest1->intergral? -pidtest1->intergralmax: pidtest1->intergral; 
     //限幅

output+=pidtest1->intergral;

    pidtest1->lasterror = iError;
    output = output > pidtest1->Outputmax ? pidtest1->Outputmax : output;
    output = output<-pidtest1->Outputmax?-pidtest1->Outputmax:output;//对输出进行限幅
    return output;
}

float PID_IncrementalPID(PID* pidtest1)//增量式pid
{
 float output, iError;
 iError = pidtest1->Aimposit - pidtest1->Nowposit;
 output=pidtest1->kp*iError - pidtest1->ki*pidtest1->lasterror + pidtest1->kd*pidtest1->preverror;
pidtest1->preverror=pidtest1->lasterror;
pidtest1->lasterror=iError;
output = output > pidtest1->Outputmax ? pidtest1->Outputmax : output;//对输出进行限幅
output= output<-pidtest1->Outputmax?-pidtest1->Outputmax:output;

return output;
}

/*int main()
{
    PID* car1=NULL;
    car1=(PID*) malloc(sizeof(PID));
    //car1=malloc(sizeof PID)
    PID_Init(car1);

    
    float kki, kkp, kkd, max1;
    printf("please set I P D and outputmax");
    scanf("%f %f %f %f", &kki, &kkp ,&kkd,&max1);


    PID_SetParameter(car1, kki, kkp, kkd,max1);
    printf( "Nowposit and aimposit"); 
    float nowposit, aimposit, outputfinal;


    scanf("%f %f",&nowposit,&aimposit);

    car1->Nowposit = nowposit;
    car1->Aimposit = aimposit;

int a;

printf("输入1使用位置式 输入2使用前馈式");
scanf("%d",&a);
switch (a)

{
case 1:
    {
    for (int i = 0; i < 100; i++)
    {
        outputfinal = PID_PostionalPID(car1);
        printf("%f" ,nowposit+outputfinal);
        printf("\n");
        nowposit=nowposit+outputfinal;
        car1->Nowposit=nowposit;
      
    }
   
}

    case 2:
    {for (int i = 0; i < 100; i++)
    {
        outputfinal = PID_IncrementalPID(car1);
        printf("%f" ,nowposit+outputfinal);
        printf("\n");
        nowposit=nowposit+outputfinal;
        car1->Nowposit=nowposit;
       
        }
       
    }

}
free(car1);

}*/

