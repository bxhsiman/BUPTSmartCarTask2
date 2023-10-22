#include <stdio.h> 
#include "PID.h" 
int main() {
	PID pid;
	double setpoint = 10.0;
	double current_value = 5.0; 
	printf("�����뱾��ʹ�õ�PID����:\n");
	PID_Initi(&pid);

	printf("your set point(goal) :");
	scanf_s("%lf", &setpoint);
	printf("the current value is:");
	scanf_s("%lf", &current_value);
	printf("kP:");
	scanf_s("%lf", &pid.kp);
	printf("kI:");
	scanf_s("%lf", &pid.ki);
	printf("kD:");
	scanf_s("%lf", &pid.kd);
	
	PID_SetParameters(&pid, pid.kp, pid.ki, pid.kd);
	double output_positional = PID_PositionalPIDs(&pid, setpoint, current_value);
	double output_incremental = PID_IncrementalPIDs(&pid, setpoint, current_value);

	printf("%-30s", "��ͨλ��ʽpid"); printf("%-30s", "��ͨ����ʽpid");printf( "%s", "ǰ������ʽpid\n");
	printf("%s%.2f", "Positional Output :", output_positional);printf( "\t%s%.2f", "Incremental Output :", output_incremental);
	if (scanf_s("%f\n", &setpoint) != 1 || scanf_s("%f\n", &current_value) != 1) {
		printf("�������");
		return 1;
	}
	return 0;
}
