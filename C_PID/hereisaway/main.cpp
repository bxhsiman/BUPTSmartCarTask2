#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include "PID.h"
int main(){
	db now_pos=0,target_pos,kp,ki,kd,output_sum=0;
	//ʱ����Ϊ���� 
	srand((unsigned int)time(NULL));
	printf("������Ŀ�꣺");
	scanf("%lf",&target_pos);
	printf("���������\n");
	printf("kp:");
	scanf("%lf",&kp);
	printf("ki:");
	scanf("%lf",&ki);
	printf("kd:");
	scanf("%lf",&kd);
	printf("��ͨλ��ʽpid:\t��ͨ����ʽpid��\n");
	//�����������ֱ����λ��ʽ������ʽ������ָ����ָ��� 
	PID* pid1=PID_Init(kp,ki,kd,target_pos);
	PID* pid2=PID_Init(kp,ki,kd,target_pos);
	//ģ��100�� 
	for(int i=1;i<=100;i++){
		//λ��ʽ 
		now_pos+=PID_PositionalPID(pid1,now_pos)+rand()%10-5;
		printf("E:%lf\t",now_pos-target_pos);
		//����ʽ 
		//�ȼ����������ӽ�ȥ 
		output_sum+=PID_IncrementalPID(pid2,now_pos);
		//�ٲ��� 
		now_pos+=output_sum+rand()%10-5;
		printf("E:%lf\n",now_pos-target_pos);
	}
	//�ͷſռ� 
	free(pid1);
	free(pid2);
} 
