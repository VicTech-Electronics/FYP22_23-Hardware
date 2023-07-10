#include "Operation.h"

void setup() {
  pinMode(backlight_pin, OUTPUT);

  lcd.begin(16, 2);
  Serial.begin(9600);
  serialDFPlayer.begin(9600);

  Serial.println("Initializing DFPlayer");
  if (!DFPlayer.begin(serialDFPlayer)) {  //Use softwareSerial to communicate with mp3.
    Serial.println("Fail to initialize DFPlayer");
    // while(true);
  }

  Serial.println("Done");
  // Welcome messages
  lcdPrint("Welcome", ""); delay(2e3);
  lcdPrint("HAND TALK", "System"); delay(2e3);
}

void loop() {
  operation();
  delay(1e3);
}
