#include <HCSR04.h>
UltraSonicDistanceSensor ultrasonic(6, 7); 

// Definition of pin connections
#define red_led_pin A1
#define yellow_led_pin A2
#define green_led_pin A3

// Definition of useful constants 
#define red_light_duration 5000      // Duration of red light in milliseconds
#define yellow_light_duration 2000   // Duration of yellow light in milliseconds
#define green_light_duration 5000    // Duration of green light in milliseconds

// Decralation of usefull variables
float distance, allowed_distance=10;


// Method to control trafic lights
void TraficLight(){
    // Red light
  digitalWrite(green_led_pin, LOW);
  digitalWrite(yellow_led_pin, LOW);
  digitalWrite(red_led_pin, HIGH);
  unsigned long initial_time = millis();
  while(millis() - initial_time < red_light_duration){
    distance = ultrasonic.measureDistanceCm();
    if(distance < allowed_distance) Serial.println("Detected");
  }

  // Red and yellow light (transition)
  digitalWrite(red_led_pin, HIGH);
  digitalWrite(yellow_led_pin, HIGH);
  delay(yellow_light_duration);

  // Green light
  digitalWrite(red_led_pin, LOW);
  digitalWrite(yellow_led_pin, LOW);
  digitalWrite(green_led_pin, HIGH);
  delay(green_light_duration);

  // Yellow light (transition)
  digitalWrite(green_led_pin, LOW);
  digitalWrite(yellow_led_pin, HIGH);
  delay(yellow_light_duration);
}