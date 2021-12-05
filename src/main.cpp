// ECE 372 Final Project
// Professor Dale Hetherington
// Fall 2021
// Authors: Nick Blanchard,

// ---------------------------------------------------------------------- //
// Libraries and source files
#include <MFRC522.h>
#include "rfid.h"
#include "switch.h"
#include "spi_new.h"
#include "timer.h"
#include "switch.h"
#include "screamingRoboBat.h"
#include "pwm.h"

// ---------------------------------------------------------------------- //
// Global Variables
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
bool inSonarRange = false;


// ---------------------------------------------------------------------- //
// State Machines
typedef enum stateEnum {wait_press, debounce_press, wait_release, debounce_release, unlocked, normal} stateEnum;
typedef enum sonarEnum {wait_high, wait_low} sonarEnum;

volatile sonarEnum echoSignal = wait_high; 
volatile stateEnum button_state = wait_press; // ASSUMING WE BEGIN IN A STATE WHERE THE BUTTON IS NOT BEING PRESSED
volatile stateEnum operation_state = normal;  // ASSUMING WE BEGIN IN A STATE OF NORMAL OPERATION



// ---------------------------------------------------------------------- //
// Main Function
int main(void) {
  // Variables
  //unsigned char sonar_data;
  int num = 0;

  // Hardware initializations
  init();  // NOTE: This function is included in the 'main' function within the Arduino core library.
           // Due to our redefinition of 'main', we must include this function call within our new 'main'.
  #if defined(USBCON)
      USBDevice.attach();
  #endif
      
  Serial.begin(9600);		// Initialize serial port
  SPI_MASTER_Init();    // Initialize SPI bus
  init_rfid();          // Initialize RFID module
  initSwitchPD0();
  initPWMTimer3();
  initTimer4();
  initTimer1();
  initSonar();
  sei(); 
  change_frequency(50);
  initTimer0();

  // MAIN LOOP
  while(1) {

    // SEND SONAR PULSE AND READ RESPONSE
    sendPulse();
      switch(echoSignal){
        case wait_high:
          TCNT4 = 0;
        break;
        case wait_low:
          TCNT4 = 0;
        break;
      }
    
    // BUTTON STATE MACHINE
    switch(button_state) {
      case wait_press:
        // Do nothing; we are waiting for the button to be pressed.
        break;
      case debounce_press:
        // Wait for the noisy 'debounce' state to pass. Then, we are awaiting release.
        delayMs(1);
        button_state = wait_release;
        break;
      case wait_release:
        // Do nothing; we are waiting for the button to be released.
        break;
      case debounce_release:
        // The button has been released.
        // Wait for the noisy 'debounce' state to pass. Then, we are awaiting press.
        delayMs(1);
        button_state = wait_press;
        break;
    }

    // IF WE ARE OPERATING NORMALLY
    if(operation_state == normal) {
      
      TURNCOUNTERCLOCKWISE();

      num = read_rfid();

      if(inSonarRange | (num == 535)) {
        Serial.println("<<<<<<OPENING DOOR>>>>>>");
        // OPEN THE DOOR
        delayMs(5000);
        TURNCLOCKWISE();
        delayMs(5000);
      }
    }

    // OTHERWISE, UNLOCK
    else {
      Serial.println("buttonUnlock");
      TURNCLOCKWISE();
    }
  }
 
  return 0;
}



// ---------------------------------------------------------------------- //
// Interrupt Service Routines

ISR (INT0_vect) {
  Serial.println("Button triggered");
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

// ---------------------------------------------------------------------- //
// Interrupt Service Routines
ISR(PCINT0_vect){ //Main code is interrupted if the switch connected to pin  changes
  //Serial.println(TCNT4);
  if(echoSignal == wait_high){
    echoSignal = wait_low;
  }
  else { 
    if(TCNT4 < inches(10)){//Within (roughly) 12 inches away from the device the condition is true
      inSonarRange = true;
    }
    else{
      inSonarRange = false;
      echoSignal = wait_high;
    }
  }
}