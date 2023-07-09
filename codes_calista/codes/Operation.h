#include "Arduino.h"
#include <stdint.h>
#include <Stepper.h>
#define step_pin 10
#define dir_pin 9

// Definition of useful pins
const uint8_t solenoid_pin=8, motor_pin=11, buzzer_pin=A0, button_pin=2, sensor_pin=A3, laser_pin=A5;

// Decralation of useful variable
float default_ldr_value, allowed_sensitivity=10, paper_out_time=2000;
bool is_started;
int half_step_delay_time = 3000;
int number_of_steps = 60;

// Method for auto calibration 
void autoCalibiration(){
  Serial.println("In calibiration");
  digitalWrite(buzzer_pin, HIGH);
  digitalWrite(laser_pin, HIGH);
  default_ldr_value = 0;
  for(int i=0; i<100; i++){
    default_ldr_value += analogRead(sensor_pin);
    delay(10);
  }
  default_ldr_value /= 100;
  Serial.println("Complete calibiration");
  digitalWrite(buzzer_pin, LOW);
}

// Method to handel Interrupt
void requestStamping(){
  Serial.println("Button is pressed");
  is_started = true;
  autoCalibiration();
}

// Methods to stamp on the paper
void solenoid(){
  digitalWrite(solenoid_pin, HIGH);
  delay(2e3);
  digitalWrite(solenoid_pin, LOW);
}

void stamp(){
  solenoid();
  digitalWrite(dir_pin, HIGH);
  for(int i=0; i<number_of_steps; i++){
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(half_step_delay_time);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(half_step_delay_time);
  }

  delay(500);
  solenoid();
  digitalWrite(dir_pin, LOW);
  for(int i=0; i<number_of_steps; i++){
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(half_step_delay_time);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(half_step_delay_time);
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
  // if(abs(analogRead(sensor_pin) - default_ldr_value) < allowed_sensitivity){
  //   digitalWrite(laser_pin, HIGH);
  //   stamp();
  //   pullPaper();
  // }else {
  //   digitalWrite(laser_pin, LOW);
  //   is_started = false;
  // }



  digitalWrite(laser_pin, HIGH);
  stamp();
  pullPaper();
}