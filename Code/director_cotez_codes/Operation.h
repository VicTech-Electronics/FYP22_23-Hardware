#include <EEPROM.h>
#include "Measure.h"
#include "Interface.h"
#include "Communication.h"

// Decralation of useful constants and variables
bool sent;
int payment;
String message;

void home_secreen(){
  Serial.println("Display parameters");
  lcdPrint("ELECTRIC METER", "Units: " + String(kWh) + "kWh");
  Serial.println();
}

void control(){
  Serial.println("LISTENING TO CONTROL");
  message = received_sms();
  
  if(message == "UNITS")
    send_sms(phone_number, "Remained units: " + String(kWh));
  else{
    payment = message.toInt();
    Serial.println("Payment message received: '" + message + "'");
    Serial.println("Payment: '" + String(payment) + "'");

    Serial.println("KWH before: " + String(kWh));
    kWh += (float(payment) / unit_price);
    Serial.println("KWH after: " + String(kWh));
    EEPROM.put(units_addr, kWh);
  }
  Serial.println();
}

void consumption(){
  Serial.println("CHECK CONSUMPTION");
  float current = 0;
  
  for(int8_t i=1; i<=2; i++){
    current =+ get_Irms();
    delay(1e3);
  }

  current = current / 2.;
  Serial.println("Average currents used");
  Serial.println("Load: " + String(current, 15));

  // Measurement is taken in Watts second (Ws)
  float Ws = (((220. * current) / 100.) * 2.); 

  // Avoiding negative consumptions
  if(Ws <= 0.0) Ws = 0.0;
  Serial.println("Average power used");
  Serial.println("Load: " + String(kWh));

  // Calculate the units remained
  kWh = kWh - Ws;

  // Avoid negative reading
  if(kWh <= 0.0) kWh = 0.0;  

  // Measure consumptions
  EEPROM.put(units_addr, kWh);
}

void switching(){
  Serial.println("SWITCHING SYSTEM");
  
  EEPROM.get(units_addr, kWh);

  Serial.println("Parameters taken from EEPROM");
  Serial.println("Units: " + String(kWh));

  if(kWh < 5.0){
    if(!sent){
      send_sms(phone, "TAARIFA \nUnit zilizobaki ni chini ya Unit 5.0");
      delay(2e3);
      send_sms(phone, "Tsh." + String(unit_price) + " = 1unit");
      sent = true; 
    }
  }
  if(kWh >= 5.0) sent = false;
  
  if(kWh > 0.0) digitalWrite(load_pin, HIGH);
  else digitalWrite(load_pin, LOW);
}