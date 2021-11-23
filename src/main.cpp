// ECE 372 Final Project
// Professor Dale Hetherington
// Fall 2021
// Authors: Nick Blanchard,

// ---------------------------------------------------------------------- //
// Libraries and source files
#include <Arduino.h>
#include "rfid.h"
#include "switch.h"

// ---------------------------------------------------------------------- //
// Global Variables
unsigned char



// ---------------------------------------------------------------------- //
// State Machines
typedef enum stateEnum {wait_press, debounce_press, wait_release, debounce_release, unlocked, normal} stateEnum;
volatile stateEnum button_state = wait_press; // ASSUMING WE BEGIN IN A STATE WHERE THE BUTTON IS NOT BEING PRESSED
volatile stateEnum operation_state = normal;  // ASSUMING WE BEGIN IN A STATE OF NORMAL OPERATION



// ---------------------------------------------------------------------- //
// Main Function
int main(void) {
  // Variables
  unsigned char sonar_data;

  // Hardware initializations
  Serial.begin(9600); // For debugging purposes
  init_rfid();        // MFRC522 RFID Module

  // Read sonar
  while(!sonar_data) {
    // Send pulse
    // Begin timer
    // 
  }

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