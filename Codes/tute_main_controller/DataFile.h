#include <SD.h>
#include <Arduino_JSON.h>
#include "Communication.h"
#include "Sense.h"

String vehicle_number = "T123-ABC";

const int chip_selector_pin = 10;
File data_file;

JSONVar json_object;

// Method to write data to SD card
void SDWrite(String file_name, String data){
  data_file = SD.open(file_name + ".txt", FILE_WRITE);
  if (data_file) {
    data_file.println(data);
    data_file.close(); 
  }
}

// Method to read sensor data and store in memory card
void storeDataInMemory(){
  getGyroData();
  smoke_value = analogSensor(smoke_pin);
  alcohol_value = analogSensor(alcohol_pin);
  vibration_value = analogSensor(vibration_pin);

  // Save the changes
  data = "Roll: " + String(roll) + String(char(223)) + "C,";
  data += " Pitch: " + String(pitch) + String(char(223)) + "C,";
  data += " Smoke: " + String(smoke_value) + "%,";
  data += " Alcohol: " + String(alcohol_value) + "%,";
  data += " Vibration: " + String(vibration_value) + "%";
  
  SDWrite("sensor_data", data);
  Serial.print("Saved data: ");
  Serial.println(data);
}