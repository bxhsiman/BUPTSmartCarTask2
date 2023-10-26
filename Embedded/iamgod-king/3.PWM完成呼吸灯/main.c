#include <REGX52.H>

sbit LED_Pin=P2^0;

unsigned int duty_cycle=0;    //pwm占空比

void Delay(unsigned int t)    //简易的延时函数
{
	while(t--);
}

void initTimer() {
    TMOD |= 0x01;  // 设置定时器0为工作模式1（16位定时器）
    TH0 = 0xFF;    // 设置计数初值，用于控制PWM的频率，可根据实际需求调整
    TL0 = 0xFF;
		ET0 = 1;  // 允许定时器0中断
    EA = 1;   // 允许总中断

    TR0 = 1;  // 启动定时器/计数器0
}

void updatePWM() interrupt 1 {
    static unsigned int counter = 0;

    TH0 = 0xFF;  // 重新加载初值
    TL0 = 0xFF;

    counter++;

    if (counter < duty_cycle) 
			{
        LED_Pin = 1;  // PWM高电平
			} 
		else 
			{
        LED_Pin = 0;  // PWM低电平
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
     Delay(10);    // 呼吸灯灭到亮的过渡延时
    }

        // 呼吸灯逐渐变暗
    for (duty_cycle = 100; duty_cycle > 0; duty_cycle--) 
		{
    Delay(10);    // 呼吸灯亮到灭的过渡延时
    }
	}
}