#include "Operation.h"

void setup() {
  gate.attach(servo_pin); 

  Serial.begin(9600);
  serialESP.begin(9600);

  // Store the calibiration value
  slot1_calibiration_value = slot1.calibiration();
  slot2_calibiration_value = slot2.calibiration();
  slot3_calibiration_value = slot3.calibiration();
  entry_calibiration_value = entry_gate.calibiration();
  exit_calibiration_value = exit_gate.calibiration();


  Serial.println("Program start");
}

void loop() {
  checkPacking();
  postData(); delay(2e3);
  
  if(serialESP.available()){ 
    Serial.println("Data received: " + payload);
    if(payload.indexOf("packing") != -1){
      JSONVar json_received_object = JSON.parse(payload);
      if((int)json_received_object["packing"] == 1)
        if(abs(entry_gate.getValue() - entry_calibiration_value) > min_allowed_value) openGate();
      if((int)json_received_object["payment"] == 1)
        if(abs(exit_gate.getValue() - exit_calibiration_value) > min_allowed_value) openGate();
    }
  }
}
