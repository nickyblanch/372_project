// ECE 372 Final Project
// Professor Dale Hetherington
// Fall 2021
// Authors: Nick Blanchard,

// ---------------------------------------------------------------------- //
// Libraries and source files
#include <Arduino.h>

// ---------------------------------------------------------------------- //
// Global Variables



// ---------------------------------------------------------------------- //
// State Machines



// ---------------------------------------------------------------------- //
// Main Function
void main() {

  // Hardware initializations
  Serial.begin(9600); // For debugging purposes
  init_rfid();        // MFRC522 RFID Module
}



// ---------------------------------------------------------------------- //
// Interrupt Service Routines