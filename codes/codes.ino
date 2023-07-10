#include "Operation.h"

void setup() {
  pinMode(ir1_pin, INPUT);
  pinMode(ir2_pin, INPUT);

  Serial.begin(9600);
  digitalWrite(dir_pin, HIGH);
}

void loop(){
  operation();
}