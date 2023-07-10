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
  float volume_change = abs(getVolume() - initial_volume);


  Serial.println("Flowrate data: " + String(flowrate_data));
  Serial.println("Volume change: " + String(volume_change));

  if(flowrate_data > 0.0 || volume_change > 0.0){
    getLocation();
    lcdPrint("Fault detected", ""); delay(2e3);
    lcdPrint("Flowrate: " + String(flowrate_data), "Volume: " + String(volume_change)); delay(3e3);

    // postRequest("www.cpbs.free.nf/ftss/getdata.php?message=Falt%20dected%20at%20Latitude:" + String(latitude, 5) + ",%20Longitude:" + String(longitude, 5));
    postRequest("www.cpbs.free.nf/ftss/getdata.php?message=victonixformgsm");
    sendSMS("WARNING: \nEmergence detected \nLatitude: " + String(latitude, 5) + "\nLongitude: " + String(longitude, 5) + "\nhttp://cpbs.free.nf/ftss/login/data.php");

  }else lcdPrint("Flowrate:" + String(flowrate_data), "Volume:" + String(volume_change));
  while(serialGSM.available()){
    gsm_data = serialGSM.readString();
    Serial.println("GSM data: " + gsm_data);  delay(5e3);
    gsm_data.trim();  
    gsm_data.toUpperCase(); 

    if(gsm_data.indexOf("RING") != -1) receiveCall();
    // else receiveSMS();
  }
}