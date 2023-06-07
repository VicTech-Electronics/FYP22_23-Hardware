#include <SoftwareSerial.h>

SoftwareSerial serial();
SoftwareSerial serialBT(10, 11);

// Definition of useful pins
const uint8_t enabel_left=1, enabel_right=24, left1=0, left2=2, right1=25, right2=26;

// Declaration of useful variables
char data;

//////////// Custome functions //////////////
// Function to listen the data from the serialBT
char listenBT(){
  if(serialBT.available()){
    Serial.println("Collect data");
    data = serialBT.read();
    Serial.print("Data ");
    Serial.println(data);
    return data;
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
  data = listenBT();
  if(data == 'F') whilesControl(true, true, true, false, true, false);
  else if(data == 'B') whilesControl(true, true, false, true, false, true);
  else if(data == 'L') whilesControl(false, true, true, false, true, false);
  else if(data == 'R') whilesControl(true, false, true, false, true, false);
  else if(data == 'S') whilesControl(false, false, true, false, true, false);
  else if(data == 'V') serial.println("horn_on");
  else if(data == 'v') serial.println("horn_off");
}


//////////// Default function ///////////////////
void setup() {
  pinMode(enabel_right,OUTPUT);
  pinMode(enabel_left, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);

  serial.begin(9600);
  Serial.begin(9600);
  serialBT.begin(9600);

  Serial.println("Program start");
}

void loop() {
  motionControl();
}
