#include "Operation.h"

/////////////// Defaul methods ///////////////
void setup() {
  pinMode(load_pin, OUTPUT);
  pinMode(backlight_pin, OUTPUT);
  
  Serial.begin(9600);
  serialGSM.begin(9600);
  lcd.begin(16, 2);
  digitalWrite(backlight_pin, HIGH);

  lcdPrint("Welcome", ""); delay(2e3);
  lcdPrint("UDSM Student", "2019-04-11366"); delay(2e3);
  lcdPrint("Energy Meter", "-------------"); delay(2e3);

  lcdPrint("Initializing...", ""); delay(3e3);
  EEPROM.get(units_addr, kWh);
  initialize_sms();
}

void loop(){
  home_secreen();
  consumption();
  switching();
  control();
}
