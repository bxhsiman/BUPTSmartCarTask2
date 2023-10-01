#include"pid.h"
#include"pid.c"
#include"stdio.h"
int main()
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

}