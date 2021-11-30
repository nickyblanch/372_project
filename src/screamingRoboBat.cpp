

#include <avr/io.h>
#include <Arduino.h>
//#include <util/delay.h>
#include "timer.h"


void initSonar(){
    DDRD |= (1<<DDD0);//Pin 21 output to send sonar trigger pulse
}
void sendPulse(){//function to trigger sonar
    PORTD |= (1<<PORTD0);
    delayUs(10);
    PORTD &= ~(1<<PORTD0);
}
int inches(int desired_inches){//converts input in inches to a rough value to compare to timer, so an object 1 inch away will trigger (roughly) when TCNT4 < 100
    return (desired_inches * 80);
}


