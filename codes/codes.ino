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
  Serial.println(F("DFPlayer Mini online."));
  DFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  DFPlayer.volume(30);  //Set volume value (0~30).
  DFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  DFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  // Welcome messages
  lcdPrint("Welcome", ""); delay(2e3);
  lcdPrint("HAND TALK", "System"); delay(2e3);
}

void loop() {
  operation();
}
