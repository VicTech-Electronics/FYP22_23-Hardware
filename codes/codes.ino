#include "Operation.h"

void setup() {
  pinMode(turbidity_pin, INPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);
  pinMode(ir1_pin, INPUT);
  pinMode(ir1_pin, INPUT);
  
  Serial.begin(9600);
}

void loop(){
  operation();
}