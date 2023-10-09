#include <reg52.h> 

sbit LED = P2^0; // LED connected to P2.0

void Timer_Init() {
    TMOD = 0x01; // Set Timer0 to Mode1 (16-bit auto-reload mode)
    TH0 = (65536 - 50000) / 256; // Set initial value for 50ms delay
    TL0 = (65536 - 50000) % 256;
    EA = 1;  // Open global interrupt switch
    ET0 = 1; // Enable Timer0 interrupt
    TR0 = 1; // Start Timer0
}

void main() {
    Timer_Init();
    while(1);
}

void Timer_ISR() interrupt 1 {
    TH0 = (65536 - 50000) / 256; // Reload initial value for 50ms delay
    TL0 = (65536 - 50000) % 256;
    LED = ~LED; // Toggle LED state
}