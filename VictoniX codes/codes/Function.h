#include "Communication.h"
#include "Sense.h"

// Definition of useful pins
const uint8_t confirm_BTN=2, cancel_BTN=3, buzzer_pin=8;

//////////// Custome functions //////////////
// Functions to handle accident confirmation and cancelation Interrupts
void confirm(){ serialESP.println("confirm"); }
void cancel(){ serialESP.println("cancel"); }
  
