#include"pid.h"
#include"pid.c"
#include<stdio.h>
int main(){
	PPID ppid;
	PPID_Init(&ppid);
	PPID_SetParameter(&ppid);
	IPID ipid;
	IPID_Init(&ipid);
	IPID_SetParameter(&ipid);
	int cnt=0;
	printf("PostionalPID:\n");
	while(cnt<300){
		float speed=PID_PostionalPID(100.0,&ppid);
		printf("%f\n",speed);
		cnt++;
	}
	printf("\n");
	printf("IncrementalPID:\n");
	int num=0;
	while(num<300){
		float speed=PID_IncrementalPID(100.0,&ipid);
		printf("%f\n",speed);
		num++;
	}
}