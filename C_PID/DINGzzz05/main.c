#include<stdio.h>
#include "pid.h"

int main()
{	
	PID* pid = PID_Init();
	int i, k;
	printf("请输入循环次数:\n");
	scanf("%d", &i);
	printf("选择位置式PID输入1，选择增量式PID输入2:\n");
	scanf("%d", &k);
	PID_SetParameter(pid);
	
	while (i>0)                                                                
	{
		i--;
		if (k == 1)
			PID_PostionalPID(pid);
		else if (k == 2)
			PID_IncrementalPID(pid);
		else printf("ERROR!!!");
	}

return 0;
}
