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

// Method to read sensor data
void readData(){
  getGyroData();
  smoke_value = analogSensor(smoke_pin);
  alcohol_value = analogSensor(alcohol_pin);
  vibration_value = analogSensor(vibration_pin);

  if(abs(old_roll - roll) >= 10 ||
    abs(old_pitch - pitch) >= 10 ||
    abs(old_smoke_value - smoke_value) >= 10 ||
    abs(old_alcohol_value - alcohol_value) >= 10 ||
    abs(old_vibration_value - vibration_value) >= 10
  ){
    Serial.println("Changes detected");

    // Save the changes
    String data_to_save = "Roll: " + String(roll) + String(char(223)) + "C \n";
    data_to_save += "Pitch: " + String(pitch) + String(char(223)) + "C \n";
    data_to_save += "Smoke: " + String(smoke_value) + "% \n";
    data_to_save += "Alcohol: " + String(alcohol_value) + "% \n";
    data_to_save += "Vibration: " + String(vibration_value) + "% \n";

    SDWrite("sensor_data", data_to_save);

    old_roll = roll;
    old_pitch = pitch;
    old_smoke_value = smoke_value;
    old_alcohol_value = alcohol_value;
    old_vibration_value = vibration_value;
  }

  if(roll > 45 || pitch > 45 ||
    vibration_value >= 50 ||
    smoke_value >= 50 ||
    digitalRead(flame_pin) == HIGH
  ){
    getLocation();
    json_object["vehicle_number"] = vehicle_number;
    json_object["latitude"] = latitude;
    json_object["longitude"] = longitude;
    json_object["description"] = "Accident detected from the sensor data readings";

    String data_to_send = JSON.stringify(json_object);
    serialESP.println(data_to_send);
  }
}