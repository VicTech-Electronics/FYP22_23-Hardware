#include "Operations.h"

void setup() {
  lcd.init();
  lcd.backlight();
  rfid.PCD_Init();
  servo1.write(0);
  servo2.write(0);
  servo1.attach(5);
  servo2.attach(6);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}
