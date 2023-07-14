#include "Operation.h"

// Definition of usefull variable
String data;
bool internet_connected = false;

// Method to wait for WiFi connection
void connection() {
  if(!serialESP.available()) {
    if (!internet_connected){
      lcdPrint("Internet", "Connecting.");
      lcdPrint("Internet", "Connecting..");
    }
  } else{
    data = serialESP.readString();
    Serial.println(data);
  }
}

    


void setup() {
  pinMode(valve_pin, OUTPUT);
  pinMode(flowrate_pin, INPUT);

  Serial.begin(9600);
  serialESP.begin(9600);
  EEPROM.get(units_address, units);

  lcd.init();
  lcd.backlight();

  connection();
  while (data.indexOf("CONNECTED") < 0) {
    connection();
    delay(1e3);
  }
  internet_connected = true;
  lcdPrint("Internet", "CONNECTED");
  delay(1e3);
}

void loop() {
  operation();
}
