#include "PID.h"
int main()
{
	PID pid;
	PID* ptr=&pid;
	PID_Init(ptr);
	PID_SetParameter( ptr);//p0.2 i0.5 d0.05
	int goal=1000;
	printf("����\n��ͨλ��ʽPID:\t��ͨ����ʽPID:\n"); 
	 
	int i=0;
	int positionalValue,incrementalValue; 
	while(i<=50)
	{
		printf("%d\t\t%d\n",PositionalPID(ptr,goal),IncrementalPID(ptr,goal));
		i++;
	}
	return 0;
}



