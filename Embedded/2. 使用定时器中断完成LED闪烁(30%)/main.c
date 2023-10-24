#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Timer0.h"

sbit LED = P1^0;  // 定义LED连接的引脚

unsigned char Sec = 55, Min = 59, Hour = 23;

void main()
{
    LCD_Init();
    Timer0Init();
    
    LCD_ShowString(1, 1, "Clock:");    // 上电显示静态字符串
    LCD_ShowString(2, 1, "  :  :");
    
    while (1)
    {
        LCD_ShowNum(2, 1, Hour, 2);    // 显示时分秒
        LCD_ShowNum(2, 4, Min, 2);
        LCD_ShowNum(2, 7, Sec, 2);
        
        // 在这里添加LED闪烁代码
        LED = !LED;  // 切换LED状态
        Delay1ms(500);  // 500毫秒延迟，控制LED闪烁速度
    }
}

void Timer0_Routine() interrupt 1
{
    static unsigned int T0Count;
    TL0 = 0x18;      // 设置定时初值
    TH0 = 0xFC;      // 设置定时初值
    T0Count++;
    if (T0Count >= 1000)    // 定时器分频，1s
    {
        T0Count = 0;
        Sec++;            // 1秒到，Sec自增
        if (Sec >= 60)
        {
            Sec = 0;        // 60秒到，Sec清0，Min自增
            Min++;
            if (Min >= 60)
            {
                Min = 0;    // 60分钟到，Min清0，Hour自增
                Hour++;
                if (Hour >= 24)
                {
                    Hour = 0;    // 24小时到，Hour清0
                }
            }
        }
    }
}
