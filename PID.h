#include <math.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <unistd.h> 

typedef struct {
	int goal;
	int CurrentValue;
	int adjust;
	
	float KP;
	float KI;
	float KD;
	
	int CurrentError ;
	int SumError;
	int LastError ;//上次误差 
	int PrevError;//上上次误差 
	
}PID ;

void PID_Init (PID * ptr)
{
	
	ptr->goal=0;
	ptr->CurrentValue=0; 
	ptr->adjust=0; 
	ptr->KP=0;
	ptr->KI=0;
	ptr->KD=0;
	ptr->CurrentError=0;
	ptr->SumError=0;
	ptr->LastError=0;
	ptr->PrevError=0;
 } 
 
 void PID_SetParameter(PID* ptr)
 {
 	float p,i,d;
 	printf("输入本次使用的PID参数\n");
    scanf("%f%f%f",&p,&i,&d);
	ptr->KP=p;
	ptr->KI=i;
	ptr->KD=d;
 }
 
 int PositionalPID(PID* ptr, int goal)
 {
 	ptr->goal=goal;
 	ptr->CurrentError=ptr->goal-ptr->CurrentValue;
 	ptr->SumError+=ptr->CurrentError;
 	ptr->adjust=ptr->KP*ptr->CurrentError+ptr->KI*ptr->SumError+ptr->KD*(ptr->CurrentError-ptr->LastError);
	ptr->CurrentValue+=ptr->adjust; 
	ptr->LastError=ptr->CurrentError;
	return ptr->CurrentValue; 
 }
 
 
 int  IncrementalPID(PID *ptr,int goal)
 {
 	int pError,iError,dError;
 	ptr->goal=goal;
 	ptr->CurrentError=goal-ptr->CurrentValue;
 	pError=ptr->CurrentError-ptr->LastError;
 	iError=ptr->CurrentError;
 	dError=ptr->CurrentError-2*(ptr->LastError)+ptr->PrevError;
 	ptr->adjust=ptr->KP*pError+ptr->KI*iError+ptr->KD*dError;
 	ptr->CurrentValue+=ptr->adjust;
 	ptr->PrevError=ptr->LastError;
 	ptr->LastError=ptr->CurrentError;
 	return ptr->CurrentValue; 
 }
 
