#include <REGX52.H>
typedef unsigned int u16;	//��ϵͳĬ���������ͽ����ض���
typedef unsigned char u8;
sbit LED1=P2^0;//����LED1�ܽ�
sbit KEY3=P3^2;//�����������K3���ƽ�
void Delay100ms()		//@12.000MHz
{
	unsigned char data i, j;
	i = 195;
	j = 138;
	do
	{
		while (--j);
	} while (--i);
}
void exti0_init(void)
{
	IT0=1;//�����ش�����ʽ���½��أ�
	EX0=1;//��INT0���ж�����
	EA=1;//�����ж�
}
void main()
{	
	exti0_init();//�ⲿ�ж�0����

	while(1)
	{

	}
}
void exti0() interrupt 0 //�ⲿ�ж�0�жϺ���
{
	Delay100ms();//����
	if(KEY3==0)//�ٴ��ж�K3���Ƿ���
		LED1=!LED1;//LED1״̬��ת					
}