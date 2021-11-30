#ifndef RFID_H
#define RFID_H
#include <MFRC522.h>

extern MFRC522 mfrc522;

void init_rfid();
void read_rfid();

#endif