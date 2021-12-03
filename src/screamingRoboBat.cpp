#include <avr/io.h>
#include <Arduino.h>
//#include <util/delay.h>
#include "timer.h"


void initSonar() {
    DDRD |= (1<<DDD1); //Pin 20 output to send sonar trigger pulse

    DDRB &= (~(1<<DDB4));//Configures PORTB data direction as input
    PORTB |= (1<<PORTB4);//Enables Pull-Up Resistors for PORTB4 pin10
    PCICR |= (1<<PCIE0);//Enables PCINT 0-7
    PCMSK0 |= (1<<PCINT4);//Enables PCINT4 pin10
}
void sendPulse() { //function to trigger sonar
    PORTD |= (1<<PORTD1);
    delayUs(10);
    PORTD &= ~(1<<PORTD1);
}
int inches(int desired_inches) { //converts input in inches to a rough value to compare to timer, so an object 1 inch away will trigger (roughly) when TCNT4 < 100
    return (desired_inches * 80);
}


