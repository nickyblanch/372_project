// ECE 372 Final Project
// Professor Dale Hetherington
// Fall 2021
// Authors: Nick Blanchard, Nicholas Gullo, Salman Marafie, Konner Curtis

#ifndef RFID_H
#define RFID_H
#include <MFRC522.h>

extern MFRC522 mfrc522;

void init_rfid();
int read_rfid();

#endif