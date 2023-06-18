#include "HardwareSerial.h"
#include "WString.h"
#include "Measure.h"
#define espRx 10
#define espTx 9
SoftwareSerial serialESP(espRx, espTx);

String path = "127.0.0.1:8000/predict-app/process_data/";
int deviceID = 900;

// Method to correct data to send
String collectData(){
  ph_val = ph();
  hum_val = dht.readHumidity();
  temp_val = dht.readTemperature();
  nitro_val = nitrogen(); delay(250);
  nitro_val = nitrogen(); delay(250);
  phos_val = phosphorous(); delay(250);
  pota_val = potassium(); delay(250);
  
  String data_to_send = "{\"deviceId\":" + String(deviceID);
  data_to_send += ",\"n\":" + String(nitro_val);
  data_to_send += ",\"p\":" + String(phos_val);
  data_to_send += ",\"k\":" + String(pota_val);
  data_to_send += ",\"temp\":" + String(temp_val);
  data_to_send += ",\"humidity\":" + String(hum_val);
  data_to_send += ",\"ph\":" + String(ph_val) + "}";
  return data_to_send;
}

// Method to send data to ESP
void sendToESP(){
  mod.listen(); delay(500);
  String full_path_to_request = path + collectData();
  Serial.println("Full path: " + full_path_to_request);
  delay(1e3);

  serialESP.listen(); delay(500);
  serialESP.println(full_path_to_request);
  delay(1e3);
}