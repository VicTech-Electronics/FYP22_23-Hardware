#include "Interface.h"
#include "Sense.h"
#include "Communication.h"


// Decralation of usefull variables
float initial_volume;
float mini_allowed_error = 200, flowrate_error = 10;

// Method to handle Interrupt button
void listenBtn(){
  button = true;
}

// Method to commbine all operations
void operation(){
  float flowrate_data = getFlowRate();
  float volume_change = abs(getVolume() - initial_volume);

  if(flowrate_data > flowrate_error || volume_change > mini_allowed_error){
    lcdPrint("FAULT DETECTED", "FR: " + String(flowrate_data) + " VC: " + String(volume_change));
    json_object["device"] = device_number;
    json_object["title"] = "FAULT DETECTION";
    json_object["content"] = "Frowrate: " + String(flowrate_data) + " L/min \n Volume change: " + String(volume_change) + " metercube";
    json_object["latitude"] = latitude;
    json_object["longitude"] = longitude;

    String json_string = JSON.stringify(json_object);
    postData("/api/report/", json_string);
    sendSMS("WARNING: \n Emergence detected \n gee-fyp22-23.herokuapp.com");

  }else lcdPrint("SAFE", "FR: " + String(flowrate_data) + " VC: " + String(volume_change));

  serialGSM.listen();
  while(serialGSM.available()){
    gsm_data = serialGSM.readString();
    gsm_data.trim();  
    gsm_data.toUpperCase();
    if(gsm_data.indexOf("RING") != -1) receiveCall();
    else receiveSMS();
  }
}