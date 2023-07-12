#include "Arduino.h"
// Definition of pin connection
const uint8_t btn1_pin=2, btn2_pin=3, buzzer_pin=7, control_pin=9, ind_pin=A5,
              switch_pin1=10, switch_pin2=11,switch_pin3=12, switch_pin4=13;

// Decralation of usefull variables
bool motor_state, in_operation;

// Methode to handle ISR for motor state
void switchON(){
  motor_state = true;
  in_operation = true;
  Serial.println("ON btn pressed");
}
void switchOFF(){
  motor_state = false;
  in_operation = true;
  Serial.println("OFF btn pressed");
}


// Method to swich relay
void relay(bool state){
  digitalWrite(switch_pin1, state);
  digitalWrite(switch_pin2, state);
  digitalWrite(switch_pin3, state);
  digitalWrite(switch_pin4, state);
}

// Method to control soft stater
float time_period = 200; // 5 sec
int interval = 120000;
void softStart(){
  Serial.println("SoftStart");
  digitalWrite(buzzer_pin, HIGH);
  for(int i=0; i<=time_period; i+=interval){
    digitalWrite(control_pin, HIGH);
    delay(i);
    digitalWrite(control_pin, LOW);
    delay(time_period - i);
    Serial.println(i);
  }
  digitalWrite(buzzer_pin, LOW);
  digitalWrite(ind_pin, HIGH);
  delay(1e3); relay(HIGH); 
  in_operation = false;
}

void softStop(){
  Serial.println("SoftStop");
  delay(1e3); relay(LOW);
  digitalWrite(buzzer_pin, HIGH);
  for(int i=0; i<=time_period; i+=interval){
    digitalWrite(control_pin, HIGH);
    delay(time_period - i);
    digitalWrite(control_pin, LOW);
    delay(i);
    Serial.println(i);
  }
  digitalWrite(buzzer_pin, LOW);
  digitalWrite(ind_pin, LOW);
  in_operation = false;
}
