#include <MFRC522.h>
#include <SPI.h>
#include <Arduino.h>
#include "rfid.h"

// ---------------------------------------------------- //
MFRC522 mfrc522(53, 5);  // Create MFRC522 instance
// 53 = SS, 5 = RST

void init_rfid() {
    // Initialized the hardware on the MEGA2560 and the MFRC522
    // for SPI communication.

    SPI.begin(); 		// Initialize SPI bus
    mfrc522.PCD_Init(); // Initialize RFID reader

}

void read_rfid() {
    
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
