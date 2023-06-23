#include "Operation.h"

void setup() {
  pinMode(lock_pin, OUTPUT);
  pinMode(btn1_pin, INPUT_PULLUP);
  pinMode(btn2_pin, INPUT_PULLUP);
  pinMode(coin_acceptor_pin, INPUT_PULLUP);


  Serial.begin(9600);
  lcd.begin(16, 2);

  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  servo3.attach(servo3_pin);

  lcdPrint("Welcome", ""); delay(2e3);
  lcdPrint("Coin change", "Provider"); delay(2e3);

  attachInterrupt(digitalPinToInterrupt(btn1_pin), confirmIRS, FALLING);
  attachInterrupt(digitalPinToInterrupt(coin_acceptor_pin), countPulseISR, FALLING);

}

void loop() {
  operation();
}
