
#ifndef TIMER_H
#define TIMER_H
#include <avr/io.h>
#include<Arduino.h>

void initTimer0();
void initTimer1();

void delay_Ms(unsigned int delay);
void delay_s(unsigned int delay);

#endif
