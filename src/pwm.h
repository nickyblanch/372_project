// ECE 372 Final Project
// Professor Dale Hetherington
// Fall 2021
// Authors: Nick Blanchard, Nicholas Gullo, Salman Marafie, Konner Curtis

#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include <Arduino.h>
#include "timer.h"

void initPWMTimer3();
void change_frequency(unsigned int freq_val);
void ChangeDutyCycle(double Direction);
void TURNCLOCKWISE();
void TURNCOUNTERCLOCKWISE();
void TURNTOMIDDLE();

#endif