// ECE 372 Final Project
// Professor Dale Hetherington
// Fall 2021
// Authors: Nick Blanchard,

// ---------------------------------------------------------------------- //
// Libraries and source files
#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>
//#include "rfid.h"
//#include "switch.h"

// ---------------------------------------------------------------------- //
// Global Variables
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


// ---------------------------------------------------------------------- //
// State Machines
typedef enum stateEnum {wait_press, debounce_press, wait_release, debounce_release, unlocked, normal} stateEnum;
volatile stateEnum button_state = wait_press; // ASSUMING WE BEGIN IN A STATE WHERE THE BUTTON IS NOT BEING PRESSED
volatile stateEnum operation_state = normal;  // ASSUMING WE BEGIN IN A STATE OF NORMAL OPERATION



// ---------------------------------------------------------------------- //
// Main Function
int main(void) {
  // Variables
  //unsigned char sonar_data;

  // Hardware initializations
  Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
  Serial.println("Entering PCD_Init()");
	mfrc522.PCD_Init();		// Init MFRC522
	Serial.println("Exiting PCD_Init()");
  _delay_ms(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

/*
  // Read sonar
  while(!sonar_data) {
    // Send pulse
    // Begin timer
    // 
  }
  */

 while(1) {

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
    // Do nothing
	}
	else if ( ! mfrc522.PICC_ReadCardSerial()) {
    // Do nothing
	}
	else {
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  }

 } // End while loop

  return 0;
}



// ---------------------------------------------------------------------- //
// Interrupt Service Routines

ISR (INT0_vect) {
  // When the interrupt flag is triggered:

  if (button_state == wait_press) {
    // The button was pushed while we were waiting for it to be pressed. Enter the first debounce state.
    button_state = debounce_press;
  }
  else if (button_state == wait_release) {
    // The button was released while we were waiting for it to be released. Enter the second debounce state.
    button_state = debounce_release;

    // Update the mode of operation
    if (operation_state == normal) {
      operation_state = unlocked;
    }
    else {
      operation_state = normal;
    }
    
  } // end if/else
  // If the flag triggers while the button is 1 in one of the noisy debounce states, we do nothing.
} // end ISR

ISR(PCINT0_vect) {

  // Stop timer
  // Read timer value
  // Reset timer to zero; disable timer
  // Set global variable sonar_data


}