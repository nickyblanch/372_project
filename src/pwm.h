#ifndef PWM_H
#define PWM_H
void initPWMTimer4();
void change_frequency(unsigned int freq_val);
void ChangeDutyCycle(double Direction);
void TURNCLOCKWISE();
void TURNCOUNTERCLOCKWISE();
void TURNTOMIDDLE();

#endif