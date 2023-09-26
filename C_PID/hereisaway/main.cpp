#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include "PID.h"
int main(){
	db now_pos=0,target_pos,kp,ki,kd,output_sum=0;
	//时间作为种子 
	srand((unsigned int)time(NULL));
	printf("请输入目标：");
	scanf("%lf",&target_pos);
	printf("请输入参数\n");
	printf("kp:");
	scanf("%lf",&kp);
	printf("ki:");
	scanf("%lf",&ki);
	printf("kd:");
	scanf("%lf",&kd);
	printf("普通位置式pid:\t普通增量式pid：\n");
	//用两个变量分别进行位置式和增量式，返回指针用指针存 
	PID* pid1=PID_Init(kp,ki,kd,target_pos);
	PID* pid2=PID_Init(kp,ki,kd,target_pos);
	//模拟100轮 
	for(int i=1;i<=100;i++){
		//位置式 
		now_pos+=PID_PositionalPID(pid1,now_pos)+rand()%10-5;
		printf("E:%lf\t",now_pos-target_pos);
		//增量式 
		//先计算增量，加进去 
		output_sum+=PID_IncrementalPID(pid2,now_pos);
		//再操作 
		now_pos+=output_sum+rand()%10-5;
		printf("E:%lf\n",now_pos-target_pos);
	}
	//释放空间 
	free(pid1);
	free(pid2);
} 
