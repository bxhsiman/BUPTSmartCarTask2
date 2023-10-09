void ADC_Init() {
    ADCON0 = 0x41; // ADC Enable and clock Fosc/8
    ADCON1 = 0xC0; // All pins as Analog, and use VDD as VREF
}

// Read ADC value
unsigned int ADC_Read(unsigned char channel) {
    if(channel > 7) // If Invalid channel selected 
        return 0;  

    ADCON0 &= 0xC5; // Clearing the Channel Selection Bits
    ADCON0 |= channel<<3; // Setting the required Bits
    __delay_ms(2); // Acquisition time to charge hold capacitor
    GO_nDONE = 1; // Initializes A/D Conversion
    while(GO_nDONE); // Wait for A/D Conversion to complete
    return ((ADRESH<<8)+ADRESL); // Returns Result
}

void main() {
    unsigned int ADC_Value;
    ADC_Init(); // Initialize ADC

    while(1) {
        ADC_Value = ADC_Read(0); // Read the ADC value of channel zero
        
    }
}