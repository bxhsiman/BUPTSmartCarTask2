#include <REG52.H>

unsigned char count = 0;  // ����������

sbit LED = P2^0;  // ����LEDΪP1�ڵĵ�0λ

void Timer_Init(void) {
    TMOD = 0x01;  // ���ö�ʱ��0Ϊģʽ1
    TH0 = 0xff;  // ���ü���ֵ
    TL0 = 0x00;
    ET0 = 1;  // ������ʱ���ж�
    EA = 1;  // �������ж�
    TR0 = 1;  // ������ʱ��0
}

void main() {
    Timer_Init();

    while (1) 
			{
        // �������п��������������
			}
}
/*
void Timer0_Int() interrup 1 {
    count++;
    if (count == 10) {  // ������10֮��תLED�Ƶ�״̬
        LED = ~LED;
        count = 0;
    }
}
*/