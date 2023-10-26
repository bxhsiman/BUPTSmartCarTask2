#include <REGX52.H>

sbit LED_Pin=P2^0;

unsigned int duty_cycle=0;    //pwmռ�ձ�

void Delay(unsigned int t)    //���׵���ʱ����
{
	while(t--);
}

void initTimer() {
    TMOD |= 0x01;  // ���ö�ʱ��0Ϊ����ģʽ1��16λ��ʱ����
    TH0 = 0xFF;    // ���ü�����ֵ�����ڿ���PWM��Ƶ�ʣ��ɸ���ʵ���������
    TL0 = 0xFF;
		ET0 = 1;  // ����ʱ��0�ж�
    EA = 1;   // �������ж�

    TR0 = 1;  // ������ʱ��/������0
}

void updatePWM() interrupt 1 {
    static unsigned int counter = 0;

    TH0 = 0xFF;  // ���¼��س�ֵ
    TL0 = 0xFF;

    counter++;

    if (counter < duty_cycle) 
			{
        LED_Pin = 1;  // PWM�ߵ�ƽ
			} 
		else 
			{
        LED_Pin = 0;  // PWM�͵�ƽ
			}

    if (counter >= 100) 
			{
        counter = 0;
			}
}
 
void main()
{
	initTimer();
	while(1)
	{
		for (duty_cycle = 0; duty_cycle <= 100; duty_cycle++) 
		{
     Delay(10);    // �����������Ĺ�����ʱ
    }

        // �������𽥱䰵
    for (duty_cycle = 100; duty_cycle > 0; duty_cycle--) 
		{
    Delay(10);    // ������������Ĺ�����ʱ
    }
	}
}