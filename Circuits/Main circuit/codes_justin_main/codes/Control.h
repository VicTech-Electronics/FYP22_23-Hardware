#include <SoftwareSerial.h>

// Objects
SoftwareSerial serialBT(2, 3);

// Definition of useful pins
const uint8_t enabel=A2, left1=A1, left2=A0, right1=A3, right2=A4;

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
  }  
  return 'n';
}

// Function to control car wheels
void whilesControl(bool en, bool l1, bool l2, bool r1, bool r2){
  Serial.println("Control wheels");
  digitalWrite(enabel, en);
  digitalWrite(left1, l1);
  digitalWrite(left2, l2);
  digitalWrite(right1, r1);
  digitalWrite(right2, r2);
}


// Function to control car motion
void motionControl(char data){
  Serial.println("Received in motionControl: " + String(data));
  if(data == 'F') whilesControl(true, true, false, true, false);
  else if(data == 'B') whilesControl(true, false, true, false, true);
  else if(data == 'L') whilesControl(true, false, false, true, false);
  else if(data == 'R') whilesControl(true, true, false, false, false);
  else if(data == 'S') whilesControl(false, false, false, false, false);
}