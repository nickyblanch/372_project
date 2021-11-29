#include <avr/io.h>
#include "pwm.h"

#include <Arduino.h>
const double CLOCKWISE= 0.1;
const double  COUNTERCLOCKWISE= 0.05;
const double MIDDLE= 0.075;

void initPWMTimer4() {

    // set DDR for output pin
    // We are using PORTH5 (pin 8 on board) (this is the OCR1C output pin)
    //
    // NOTE: When using Mode 15, OCR4A is needed to set the top value. Therefore, we must
    // use OCR1C for out output compare, and out output pin must be PH5 (pin 8).
    DDRH |= (1 << DDH5);

    // We will use PWM mode 15 (so we can vary frequency)
    // WGM13 = 1, WGM12 = 1, WGM11 = 1, WGM10 = 1 (these bits are stored in the TCCR1A and TCCR1B registers)
    TCCR4A |= ((1 << WGM40) | (1 << WGM41));
    TCCR4B |= (1 << WGM43);
    TCCR4B |= (1 << WGM42);

    // Frequency calculation:
    // We will use a prescaler of 256. The 'top value' is OCR4A.
    // fpwm = fclk / (prescaler * (1 + top value)), we will use a prescaler of 256

    // Set prescaler to 254
    TCCR4B &= ~(1 << CS40);
    TCCR4B &= ~(1 << CS41);
    TCCR4B |= (1 << CS42);

    // Set to non-inverting mode - output starts high and then is low
    // See table 17-4
    // Non-inverting: COM4C1 = 1, COM4C0 = 0 (located in TCCR4A register)
    TCCR4A |= (1 << COM4C1);
    TCCR4A &= ~(1 << COM4C0);
    // NOTE: When using Mode 15 (variable frequency), we use OCR1C for output compare. Therefore, we
    // need to use COM1C1 and COM1C0 here. Otherwise, we would use COM1A1 and COM1A0.


    // NOTE: OCR1C and OCR1A are NOT set here. To determine the frequenc and duty cycle,
    // they must be set by the change_frequency function.
    OCR4C = OCR4A * 0.1;       // 10% duty cycle
}

void change_frequency(unsigned int freq_val) {
    // To vary the frequency, we need to to change OCR1A (the TOP value) and OCR4C (the COMPARE value)
    OCR4A = (16000000/freq_val)/256;  // (ignoring the 1 in the formula)
    
}
void ChangeDutyCycle(double Direction){
     OCR4C = OCR4A * Direction;   
}
void TURNCLOCKWISE(){
    
    _delay_ms(5);

    ChangeDutyCycle(CLOCKWISE);
       Serial.println("turning");
}
void TURNCOUNTERCLOCKWISE(){
    
    _delay_ms(5);

    ChangeDutyCycle(COUNTERCLOCKWISE);
}
void TURNTOMIDDLE(){
    
    _delay_ms(5);

    ChangeDutyCycle(MIDDLE);

}