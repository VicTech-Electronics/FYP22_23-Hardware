#include "Operation.h"
void setup() {
  pinMode(ind1_pin, OUTPUT);
  pinMode(ind2_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(switch1_pin1, OUTPUT);
  pinMode(switch1_pin2, OUTPUT);
  pinMode(switch1_pin3, OUTPUT);
  pinMode(switch2_pin1, OUTPUT);
  pinMode(switch2_pin2, OUTPUT);
  pinMode(switch2_pin3, OUTPUT);
  pinMode(breaker_pin, INPUT_PULLUP);

  Serial.begin(9600); 
  delay(5e3); 
  initializeSMS();
}

void loop() {
  // if(digitalRead(breaker_pin)){
  //   Serial.println("Break OFF");
  //   switching(1, false);
  //   switching(2, false);
  // }else{
  //   Serial.println("Break ON");
  //   operation();
  // } 

  operation();
}
