#ifndef RFID_H
#define RFIE_H

#include <MFRC522.h>
#include <SPI.h>

extern MFRC522 mfrc522;  // Create MFRC522 instance

void init_rfid();
void read_rfid();

#endif