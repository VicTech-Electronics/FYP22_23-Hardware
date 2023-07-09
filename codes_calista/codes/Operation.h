#include "Arduino.h"
#include <stdint.h>
#include <Stepper.h>
#define step_pin 10
#define dir_pin 9

// Definition of useful pins
const uint8_t solenoid_pin=8, motor_pin=11, buzzer_pin=A0, button_pin=2, sensor_pin=A3, laser_pin=A5;

// Decralation of useful variable
float default_ldr_value, allowed_sensitivity=30, paper_out_time=2000;
bool is_started, stamping;
int half_step_delay_time = 3000;
int number_of_steps = 90 * 200 / 360.0;;

// Define the motor steps per revolution
const int STEPS_PER_REVOLUTION = 200;
// Define the desired rotation speed in RPM
const int SPEED_RPM = 60;
// Calculate the delay between steps based on the desired spee
const long STEP_DELAY = 60L * 1000L * 1000L / (STEPS_PER_REVOLUTION * SPEED_RPM);

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

// Metho do handle ISR
void requestStamping(){
  Serial.println("Button is pressed");
  autoCalibiration();
  digitalWrite(laser_pin, HIGH);
  stamping = true;
}

// Function to rotate the stepper motor a specified number of degrees in a given direction
void rotateDegrees(float degrees, bool clockwise) {
  // Calculate the number of steps needed for the desired rotation
  int steps = degrees * STEPS_PER_REVOLUTION / 360.0;
  // Set the direction
  digitalWrite(dir_pin, clockwise ? HIGH : LOW);
  // Pulse the step pin to perform the steps
  for (int i = 0; i < steps; i++) {
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(STEP_DELAY);
  }
}

// Methods to stamp on the paper
void solenoid(){
  digitalWrite(solenoid_pin, HIGH);
  delay(2e3);
  digitalWrite(solenoid_pin, LOW);
}

void stamp(){
  solenoid();
  rotateDegrees(90, true);
  delay(500);
  solenoid();
  rotateDegrees(90, false);
}

// Method to pull paper
void pullPaper(){
  digitalWrite(motor_pin, HIGH);
  delay(paper_out_time);
  digitalWrite(motor_pin, LOW);
}

// Method to complete all operation
void completeOperation(){
  if(stamping){
    if(abs(analogRead(sensor_pin) - default_ldr_value) > allowed_sensitivity){
      Serial.println("NO paper");
      stamping = false;
      digitalWrite(laser_pin, LOW);
      delay(1e3);
    }else {
      Serial.println("Paper");
      stamp();
      pullPaper();
    }
  }else Serial.println("No stamping");
}