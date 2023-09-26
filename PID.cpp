#include "PID.h"
int main()
{
	PID pid;
	PID* ptr=&pid;
	PID_Init(ptr);
	PID_SetParameter( ptr);//p0.2 i0.5 d0.05
	int goal=1000;
	printf("误差表\n普通位置式PID:\t普通增量式PID:\n"); 
	 
	int i=0;
	int positionalValue,incrementalValue; 
	while(i<=50)
	{
		printf("%d\t\t%d\n",PositionalPID(ptr,goal),IncrementalPID(ptr,goal));
		i++;
	}
	return 0;
}



