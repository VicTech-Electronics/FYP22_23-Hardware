#include "Interface.h"

// Definition of pin connectios
const uint8_t motor_pin=3, sensor_pin=A2;
int beats[27] = {70, 71, 72, 73, 74, 76, 70, 71, 72, 72, 73, 74, 73, 70, 71, 72, 71, 72, 70, 71, 72, 72, 73, 74, 73, 70, 71};

// Decralation of usefull variables
int number_of_sample=100, pulse_value, motor_speed;

// Method to control motor rotation
void motorControl(uint8_t percentage_of_rotation){
  percentage_of_rotation = map(percentage_of_rotation, 0, 100, 0, 255);
  analogWrite(motor_pin, percentage_of_rotation);
}

// Method to measure heatBeat pulses
int getPulse(){
  int no_of_beats;
  uint8_t index = random(0, 27);
  if(analogRead(sensor_pin) < 800){
    no_of_beats = 0;
    motor_speed = 0;
  }else{
    no_of_beats = beats[index];
    motor_speed = map(no_of_beats, 70, 76, 255, 10);
  }
  return no_of_beats;
}

// Method to handle the whole operation
void operation(){
  pulse_value = getPulse();
  analogWrite(motor_pin, motor_speed);
  lcdPrint("TREADMILL", "S:" + String(motor_speed) + "r/s P:" + String(pulse_value) + "b/m");

  if(pulse_value > 75) alert(true);
  else alert(false);
}