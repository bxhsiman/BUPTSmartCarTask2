#include <REG52.H>

unsigned char count = 0;  // 计数器变量

sbit LED = P2^0;  // 定义LED为P1口的第0位

void Timer_Init(void) {
    TMOD = 0x01;  // 设置定时器0为模式1
    TH0 = 0xff;  // 设置计数值
    TL0 = 0x00;
    ET0 = 1;  // 开启定时器中断
    EA = 1;  // 开启总中断
    TR0 = 1;  // 启动定时器0
}

void main() {
    Timer_Init();

    while (1) 
			{
        // 主函数中可以添加其他代码
			}
}
/*
void Timer0_Int() interrup 1 {
    count++;
    if (count == 10) {  // 计数到10之后反转LED灯的状态
        LED = ~LED;
        count = 0;
    }
}
*/