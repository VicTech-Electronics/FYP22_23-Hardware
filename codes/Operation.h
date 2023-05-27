#include "Arduino.h"
#include <stdint.h>
#include <Stepper.h>
#define step_pin 10
#define dir_pin 9

// Definition of useful pins
const uint8_t solenoid_pin=8, motor_pin=11, buzzer_pin=A0, button_pin=2, sensor_pin=A3;

// Decralation of useful variable
float default_ldr_value, allowed_sensitivity=10, paper_out_time=2000;
bool is_started;

// Method for auto calibration 
void autoCalibiration(){
  Serial.println("In calibiration");
  digitalWrite(buzzer_pin, HIGH);
  default_ldr_value = 0;
  for(int i=0; i<100; i++){
    default_ldr_value += analogRead(sensor_pin);
    delayMicroseconds(500);
  }
  default_ldr_value /= 100;
  Serial.println("Complete calibiration");
  digitalWrite(buzzer_pin, LOW);
}

// Method to handel Interrupt
void requestStamping(){
  is_started = !is_started;
  autoCalibiration();
}

// Methods to stamp on the paper
void solenoid(){
  digitalWrite(solenoid_pin, HIGH);
  delay(1e3);
  digitalWrite(solenoid_pin, LOW);
}

void stamp(){
  solenoid();
  digitalWrite(dir_pin, HIGH);
  for(int i=0; i<50; i++){
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(500);
  }

  delay(500);
  solenoid();
  digitalWrite(dir_pin, LOW);
  for(int i=0; i<50; i++){
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(500);
  }
}

// Method to pull paper
void pullPaper(){
  digitalWrite(motor_pin, HIGH);
  delay(paper_out_time);
  digitalWrite(motor_pin, LOW);
}

// Method to complete all operation
void completeOperation(){
  if(abs(analogRead(sensor_pin) - default_ldr_value) < allowed_sensitivity){
    stamp();
    pullPaper();
  }else is_started = false;
}