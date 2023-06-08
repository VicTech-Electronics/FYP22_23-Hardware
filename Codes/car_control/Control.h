#include "Communication.h"

// Definition of useful pins
const uint8_t enabel_left=1, enabel_right=24, left1=0, left2=2, right1=25, right2=26;

// Declaration of useful variables
char bluetooth_data;

//////////// Custome functions //////////////
// Function to listen the data from the serialBT
char listenBT(){
  while(serialBT.available()){
    Serial.println("Collect data");
    bluetooth_data = serialBT.read();
    Serial.print("Data ");
    Serial.println(bluetooth_data);
    return bluetooth_data;
  } return 'n';
}

// Function to control car wheels
void whilesControl(bool en_left, bool en_right, bool l1, bool l2, bool r1, bool r2){
  digitalWrite(enabel_left, en_left);
  digitalWrite(enabel_right, en_right);
  digitalWrite(left1, l1);
  digitalWrite(left2, l2);
  digitalWrite(right1, r1);
  digitalWrite(right2, r2);
}


// Function to control car motion
void motionControl(){
  bluetooth_data = listenBT();
  if(bluetooth_data == 'F') whilesControl(true, true, true, false, true, false);
  else if(bluetooth_data == 'B') whilesControl(true, true, false, true, false, true);
  else if(bluetooth_data == 'L') whilesControl(false, true, true, false, true, false);
  else if(bluetooth_data == 'R') whilesControl(true, false, true, false, true, false);
  else if(bluetooth_data == 'S') whilesControl(false, false, true, false, true, false);
  else if(bluetooth_data == 'V') {
    serial.listen();
    if(serial.isListening()) serial.println("horn_on");
  }else if(bluetooth_data == 'v'){
    serial.listen();
    if(serial.isListening()) serial.println("horn_off");
  } 
}