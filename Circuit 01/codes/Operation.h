#include "Communication.h"
#include "Alert.h"
#include <HCSR04.h>

UltraSonicDistanceSensor ultrasonic(A1, A0);

// Definition of pin connection
const uint8_t sensor1_pin=A2, sensor2_pin=A3, valve_pin1=3, valve_pin2=4;

void openValve(bool state){
  if(state){
    digitalWrite(valve_pin1, LOW);
    digitalWrite(valve_pin2, HIGH);
    digitalWrite(green_pin, HIGH);

    delay(3e3);
    if(digitalRead(sensor2_pin) == HIGH){
      alerting(true, true);
      sendNRF('Y');
      sendSMS();
    }
  }else{
    digitalWrite(valve_pin1, HIGH);
    digitalWrite(valve_pin2, LOW);
    digitalWrite(green_pin, LOW);
  }
  delay(5e3); // Wait for valve to complete action
}

// Operation of the whole circuit start here
void operation(){
  if(digitalRead(sensor1_pin) == HIGH){ // No water in the tank
   alerting(true, true);
   sendNRF('X');
   sendSMS();
  }else alerting(false, false);

  if(ultrasonic.measureDistanceCm() <= 70) openValve(true);
  else openValve(false);
}
