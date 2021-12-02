#include "timer.h"
//You many use any timer you wish for the microsecond delay and the millisecond delay


/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
// 1 us timer
void initTimer1(){
TCCR1A &= ~(1<< WGM10);
TCCR1B |= (1<< WGM12);//This bit being 1 sets up CTC mode
TCCR1A &= ~(1<< WGM11);
TCCR1B &= ~(1<< WGM13);

TCCR1B |= (1 << CS10);
TCCR1B &= ~((1 << CS12) | (1 << CS11));//Sets prescaler to 1

OCR1A=15;
}	


/* This delays the program an amount of microseconds specified by unsigned int delay.
*/
void delayUs(unsigned int delay){
    unsigned int delayCnt = 0;
    TIFR1 |= (1<< OCF1A);//Set compare flag to start timer
    TCNT1 = 0;//Initializes timer to 0
    while(delayCnt < delay){
        if(TIFR1 & (1<<OCF1A)){
            delayCnt++;//Incrament only if flag is set and OCF1A not reached
            TIFR1 |= (1<<OCF1A);//Set timer back to all 0's 
        }
    }
}


/* Initialize timer 4, you should not turn the timer on here. Use CTC mode  .*/

//262 ms max timer
void initTimer4(){
TCCR4A &= ~(1<< WGM40);
TCCR4B |= (1<< WGM42);//This bit being 1 sets up CTC mode
TCCR4A &= ~(1<< WGM41);
TCCR4B &= ~(1<< WGM43);

TCCR4B |= ((1<< CS41) | (1<< CS40));//Sets prescaler to 64
TCCR4B &= ~(1 << CS42);

OCR4A = 65535;
}

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
TCCR0A &= ~(1<< WGM00);
TCCR0A |= (1<< WGM01);//This bit being 1 sets up CTC mode
TCCR0B &= ~(1<< WGM02);

TCCR0B |= (1<< CS02) | (1<< CS00);
TCCR0B &= ~(1 << CS01);//Sets prescaler to 1024

OCR0A = 15;//solved for a 1ms delay OCR0A=Desired ms delay * 16Mhz / Prescaler
}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-2000 milliseconds
*/
void delayMs(unsigned int delay){
    unsigned int delayCnt = 0;
    TCNT0 = 0;//Initializes timer to 0
    TIFR0 |= (1<< OCF0A);//Set compare flag to start timer
    while(delayCnt < delay){
        if(TIFR0 & (1<<OCF0A)){
            delayCnt++;//Incrament only if flag is set and OCF0A not reached
            TIFR0 |= (1<< OCF0A);//Set timer back to all 0's 
        }
    }
}
