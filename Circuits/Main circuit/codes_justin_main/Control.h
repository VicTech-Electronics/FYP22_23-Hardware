#include "Arduino.h"
#include <stdint.h>
#include <SoftwareSerial.h>
#define bt_rx 3
#define bt_tx 4
SoftwareSerial serialBT(bt_rx, bt_tx);

#define FORWARD "forward"
#define BACKWARD "backward"
#define LEFT "left"
#define RIGHT "right"
#define FORWARD_LEFT "forward_left"
#define FORWARD_RIGHT "forward_right"
#define BACKWARD_LEFT "backward_left"
#define BACKWARD_RIGHT "backward_right"
#define STOP "stop"

// Definition of pin connetions
const uint8_t wheels_enable_pin=A2, left1_pin=A1, left2_pin=A0, right1_pin=A3, right2_pin=A4;

// Decralation of usefull variables
uint8_t carSpeed;

// Method to control wheels
void wheelControl(bool enable, float left1, float left2, float right1, float right2){
  digitalWrite(wheels_enable_pin, enable);
  analogWrite(left1_pin, left1);
  analogWrite(left2_pin, left1);
  analogWrite(right1_pin, right1);
  analogWrite(right2_pin, right2);
}

// Method to control car
void carControl(String direction, int speed){
  speed * 10;
  speed = map(speed, 0, 100, 0, 255);
  float half_speed = speed/2;
  if(direction == FORWARD) wheelControl(true, speed, 0, speed, 0);
  else if(direction == BACKWARD) wheelControl(true, 0, speed, 0, speed);
  else if(direction == LEFT) wheelControl(true, 0, 0, speed, 0);
  else if(direction == RIGHT) wheelControl(true, speed, 0, 0, 0);
  else if(direction == FORWARD_LEFT) wheelControl(true, half_speed, 0, speed, 0);
  else if(direction == FORWARD_RIGHT) wheelControl(true, speed, 0, half_speed, 0);
  else if(direction == BACKWARD_LEFT) wheelControl(true, 0, half_speed, 0, speed);
  else if(direction == BACKWARD_RIGHT) wheelControl(true, 0, speed, 0, half_speed);
  else if(direction == STOP) wheelControl(false, 0, 0, 0, 0);
}

// Method to handle bluetooth serial communication
void serialBluetoothReceive(){
  byte btData;
  if(serialBT.available())
    btData = serialBT.read();
  
  if(int(btData) >= 0 &&  int(btData) < 10) carSpeed = int(btData);
  else if(btData == 'q') carSpeed = 10;
  else if(btData == 'F') carControl(FORWARD, carSpeed);
  else if(btData == 'B') carControl(BACKWARD, carSpeed);
  else if(btData == 'L') carControl(LEFT, carSpeed);
  else if(btData == 'R') carControl(RIGHT, carSpeed);
  else if(btData == 'G') carControl(FORWARD_LEFT, carSpeed);
  else if(btData == 'I') carControl(FORWARD_RIGHT, carSpeed);
  else if(btData == 'H') carControl(BACKWARD_LEFT, carSpeed);
  else if(btData == 'J') carControl(BACKWARD_RIGHT, carSpeed);
  else if(btData == 'S') carControl(STOP, 0);
}