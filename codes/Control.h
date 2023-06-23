#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

// Definition of pin connections
const uint8_t servo1_pin=A1, servo2_pin=A2, servo3_pin=A3,
              btn1_pin=3, btn2_pin=7, lock_pin=5;

// Decralation of usefull variables
bool confirm=false;
              
// Method to handle btn ISR
void confirmIRS(){
  confirm = true;
  Serial.println("IRS button is placed");
}

// Method to rotare servo
void servoRotate(Servo servo){
  for(byte i=0; i<90; i++){
    servo.write(i);
    delay(20);
  } delay(1e3);
  for(byte i=90; i>0; i--){
    servo.write(i);
    delay(20);
  }
}