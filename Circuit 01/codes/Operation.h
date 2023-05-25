#include "Communication.h"
#include "Alert.h"
#include <HCSR04.h>
#define trig A1
#define echo A0
UltraSonicDistanceSensor ultrasonic(trig, echo);

// Definition of pin connection
const uint8_t sensor1_pin=A4, sensor2_pin=A5, valve_pin1=3, valve_pin2=4;

void openValve(bool state){
  if(state){
    digitalWrite(valve_pin1, HIGH);
    digitalWrite(valve_pin2, LOW);
  }else{
    digitalWrite(valve_pin1, HIGH);
    digitalWrite(valve_pin2, LOW);
  }
}


// Operation of the whole circuit start here
void operation(){
  if(digitalRead(sensor1_pin) == HIGH){ // No water in the tank
   alerting(true, true);
   sendNRF('X');
   sendSMS();
  }
  if(digitalRead(sensor2_pin) == LOW){
    alerting(false, false);
    alerting(true, false);
    sendNRF('Y');
  }

  if(ultrasonic.measureDistanceCm() <= 70) openValve(true);
  else openValve(false);
}
