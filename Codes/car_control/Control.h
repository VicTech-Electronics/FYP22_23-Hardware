#include <SoftwareSerial.h>
#include <Arduino_JSON.h>

// Objects
SoftwareSerial serialBT(6, 7);

// Definition of useful pins
const uint8_t enabel_left=A2, enabel_right=A0, left1=A1, left2=A3, right1=A4, right2=A5;

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
void whilesControl(bool en_left, bool en_right, bool l1, bool l2, bool r1, bool r2){
  Serial.println("Control wheels");
  digitalWrite(enabel_left, en_left);
  digitalWrite(enabel_right, en_right);
  digitalWrite(left1, l1);
  digitalWrite(left2, l2);
  digitalWrite(right1, r1);
  digitalWrite(right2, r2);
}


// Function to control car motion
void motionControl(){
  serialBT.listen();
  bluetooth_data = listenBT();
  if(bluetooth_data == 'F') whilesControl(true, true, true, false, true, false);
  else if(bluetooth_data == 'B') whilesControl(true, true, false, true, false, true);
  else if(bluetooth_data == 'L') whilesControl(false, true, false, false, true, false);
  else if(bluetooth_data == 'R') whilesControl(true, false, true, false, false, false);
  else if(bluetooth_data == 'S') whilesControl(false, false, false, false, false, false);
}