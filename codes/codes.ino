#include "Control.h"

void setup(){
  pinMode(btn1_pin, INPUT_PULLUP);
  pinMode(btn2_pin, INPUT_PULLUP);
  pinMode(control_pin, OUTPUT);
  pinMode(switch_pin1, OUTPUT);
  pinMode(switch_pin2, OUTPUT);
  pinMode(switch_pin3, OUTPUT);
  pinMode(switch_pin4, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(ind_pin, OUTPUT);

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(btn1_pin), switchON, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn2_pin), switchOFF, FALLING);
}

void loop(){
  if(in_operation){
    Serial.println("is in Operation");
    if(motor_state) softStart();
    else softStop();
  }else{
    Serial.println("Out");
  }
}