#include "Operation.h"

void setup() {
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);
  pinMode(ir1_pin, INPUT);
  pinMode(ir1_pin, INPUT);
  
  Serial.begin(9600);
  digitalWrite(dir_pin, HIGH);
}

void loop(){
  operation();
}