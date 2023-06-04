#include "Interface.h"

// Definition of pin connectios
const uint8_t motor_pin=3, sensor_pin=A2;

// Decralation of usefull variables
int number_of_sample=100, pulse_value;

// Method to control motor rotation
void motorControl(uint8_t percentage_of_rotation){
  percentage_of_rotation = map(percentage_of_rotation, 0, 100, 0, 255);
  analogWrite(motor_pin, percentage_of_rotation);
}

// Method to measure heatBeat pulses
int getPulse(){
  int total = 0;
  for (int i = 0; i < number_of_sample; i++) {
    total += analogRead(sensor_pin);
    delay(10);
  }
  return map((total / number_of_sample), 0, 1023, 30, 220); // Return beat per minute
}

// Method to handle the whole operation
void operation(){
  pulse_value = getPulse();
  int motor_speed = map(pulse_value, 30, 220, 255, 100);
  analogWrite(motor_pin, motor_speed);
  lcdPrint("TREADMILL", "S:" + String(motor_speed) + "    P:" + String(pulse_value));

  if(pulse_value > 75) alert(true);
  else alert(false);
}