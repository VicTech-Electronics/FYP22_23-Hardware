#include "Interface.h"
#include "Sense.h"
#include "Communication.h"


// Decralation of usefull variables
float initial_volume;
float mini_allowed_error = 200, flowrate_error = 10;

// Method to handle Interrupt button
void listenBtn(){
  Serial.println("Button is pressed");
  button = true;
}

// Method to commbine all operations
void operation(){
  float flowrate_data = getFlowRate();
  float volume_change = 0.0;
  // abs(getVolume() - initial_volume);


  Serial.println("Flowrate data: " + String(flowrate_data));
  Serial.println("Volume change: " + String(volume_change));

  if(flowrate_data > 0.0 || volume_change > 0.0){
    getLocation();
    lcdPrint("Fault detected", ""); delay(2e3);
    lcdPrint("Flowrate: " + String(flowrate_data), "Volume: " + String(volume_change)); delay(3e3);

    // json_object["device"] = device_number;
    // json_object["title"] = "FAULT DETECTION";
    // json_object["content"] = "Frowrate: " + String(flowrate_data) + " L/min \n Volume change: " + String(volume_change) + " metercube";
    // json_object["latitude"] = latitude;
    // json_object["longitude"] = longitude;
    // String json_string = JSON.stringify(json_object);

    // postData("/api/report/", json_string);
    sendSMS("WARNING: \nEmergence detected \nLatitude: " + String(latitude, 5) + "\nLongitude: " + String(longitude, 5) + "\ngee-fyp22-23.herokuapp.com");

  }else lcdPrint("Flowrate:" + String(flowrate_data), "Volume:" + String(volume_change));
  while(serialGSM.available()){
    gsm_data = serialGSM.readString();
    Serial.println("GSM data: " + gsm_data);  delay(5e3);
    gsm_data.trim();  
    gsm_data.toUpperCase();

    if(gsm_data.indexOf("RING")) receiveCall();
    // else receiveSMS();
  }
}