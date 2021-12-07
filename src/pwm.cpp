// ECE 372 Final Project
// Professor Dale Hetherington
// Fall 2021
// Authors: Nick Blanchard, Nicholas Gullo, Salman Marafie, Konner Curtis

#include "pwm.h"

const double CLOCKWISE= 0.1;
const double  COUNTERCLOCKWISE= 0.05;
const double MIDDLE= 0.075;

void initPWMTimer3() {

    // set DDR for output pin
    // We are using PORTH5 (pin 8 on board) (this is the OCR1C output pin)
    //
    // NOTE: When using Mode 15, OCR3A is needed to set the top value. Therefore, we must
    // use OCR1C for out output compare, and out output pin must be PE5 (pin 3).
    DDRE |= (1 << DDE5);

    // We will use PWM mode 15 (so we can vary frequency)
    // WGM13 = 1, WGM12 = 1, WGM11 = 1, WGM10 = 1 (these bits are stored in the TCCR1A and TCCR1B registers)
    TCCR3A |= ((1 << WGM30) | (1 << WGM31));
    TCCR3B |= (1 << WGM33);
    TCCR3B |= (1 << WGM32);

    // Frequency calculation:
    // We will use a prescaler of 256. The 'top value' is OCR3A.
    // fpwm = fclk / (prescaler * (1 + top value)), we will use a prescaler of 256

    // Set prescaler to 256
    TCCR3B &= ~(1 << CS30);
    TCCR3B &= ~(1 << CS31);
    TCCR3B |= (1 << CS32);

    // Set to non-inverting mode - output starts high and then is low
    // See table 17-3
    // Non-inverting: COM3C1 = 1, COM3C0 = 0 (located in TCCR3A register)
    TCCR3A |= (1 << COM3C1);
    TCCR3A &= ~(1 << COM3C0);
    // NOTE: When using Mode 15 (variable frequency), we use OCR1C for output compare. Therefore, we
    // need to use COM1C1 and COM1C0 here. Otherwise, we would use COM1A1 and COM1A0.


    // NOTE: OCR1C and OCR1A are NOT set here. To determine the frequenc and duty cycle,
    // they must be set by the change_frequency function.
    OCR3C = OCR3A * 0.1;       // 10% duty cycle
}

void change_frequency(unsigned int freq_val) {
    // To vary the frequency, we need to to change OCR1A (the TOP value) and OCR3C (the COMPARE value)
    OCR3A = (16000000/freq_val)/256;  // (ignoring the 1 in the formula)
    
}
void ChangeDutyCycle(double Direction){
     OCR3C = OCR3A * Direction;   
}
void TURNCLOCKWISE(){
    delayMs(5);
    ChangeDutyCycle(CLOCKWISE);
    Serial.println("turning");
}
void TURNCOUNTERCLOCKWISE(){
    delayMs(5);
    ChangeDutyCycle(COUNTERCLOCKWISE);
}
void TURNTOMIDDLE(){
    delayMs(5);
    ChangeDutyCycle(MIDDLE);
}