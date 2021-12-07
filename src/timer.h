// ECE 372 Final Project
// Professor Dale Hetherington
// Fall 2021
// Authors: Nick Blanchard, Nicholas Gullo, Salman Marafie, Konner Curtis

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer1();
void initTimer4();
void delayUs(unsigned int delay);
void initTimer0();
void delayMs(unsigned int delay); 

#endif
