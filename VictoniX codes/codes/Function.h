#include "Communication.h"
#include "Sense.h"

// Definition of useful pins
const uint8_t enabel_left=1, enabel_right=24, left1=0, left2=2, right1=25, right2=26,
              confirm_BTN=28, cancel_BTN=27, indicator_pin=14;

//////////// Custome functions //////////////
// Functions to handle accident confirmation and cancelation Interrupts
void confirm(){ serialESP.println("confirm"); }
void cancel(){ serialESP.println("cancel"); }
  
void whilesControl(bool en_left, bool en_right, bool l1, bool l2, bool r1, bool r2){
  digitalWrite(enabel_left, en_left);
  digitalWrite(enabel_right, en_right);
  digitalWrite(left1, l1);
  digitalWrite(left2, l2);
  digitalWrite(right1, r1);
  digitalWrite(right2, r2);
}

void motionControl(){
  data = listenBT();
  if(data == "forward") whilesControl(true, true, true, false, true, false);
  else if(data == "backward") whilesControl(true, true, false, true, false, true);
  else if(data == "left") whilesControl(false, true, true, false, true, false);
  else if(data == "right") whilesControl(true, false, true, false, true, false);
  else if(data == "stop"){
    whilesControl(false, false, true, false, true, false);
    digitalWrite(indicator_pin, HIGH);
    delay(2e3);
    digitalWrite(indicator_pin, LOW);

  }
  
}
