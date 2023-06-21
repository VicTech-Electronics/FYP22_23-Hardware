#include "TraficLights.h"

void setup() {
  pinMode(red_led_pin, OUTPUT);
  pinMode(yellow_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  TraficLight();
}
