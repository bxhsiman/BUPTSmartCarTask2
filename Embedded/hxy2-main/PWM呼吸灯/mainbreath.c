#include <reg52.h>

sbit PWM_LED = P2^0; // PWM LED connected to P2.0

void Timer_Init() {
    TMOD = 0x01; // Set Timer0 to Mode1 (16-bit auto-reload mode)
    TH0 = (65536 - 50000) / 256; // Set initial value for 50ms delay
    TL0 = (65536 - 50000) % 256;
    EA = 1;  // Open global interrupt switch
    ET0 = 1; // Enable Timer0 interrupt
    TR0 = 1; // Start Timer0
}

void PWM_Init() {
    CCON = 0; // Clear CCON Register
    CMOD = 0x02; // Set C/T bits for Timer Mode
    CCAPM0 = 0x42; // Set PWM mode and ECOM bits
    CCAP0L = 0; // Initialize CCAP0L to 0
    CCAP0H = 0; // Initialize CCAP0H to 0
    CR = 1; // Start PCA counter
}

void main() {
    Timer_Init();
    PWM_Init();
    while(1) {
        // Increase brightness
        for(CCAP0L = 0; CCAP0L < 255; CCAP0L++) {
            delay(50); // Delay for smooth transition
        }
        // Decrease brightness
        for(CCAP0L = 255; CCAP0L > 0; CCAP0L--) {
            delay(50); // Delay for smooth transition
        }
    }
}

void Timer_ISR() interrupt 1 {
    TH0 = (65536 - 50000) / 256; // Reload initial value for 50ms delay
    TL0 = (65536 - 50000) % 256;
    PWM_LED = ~PWM_LED; // Toggle LED state
}