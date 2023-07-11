#include <SD.h>
#include <Arduino_JSON.h>
#include "Communication.h"
#include "Sense.h"

String vehicle_number = "T123-ABC";

const int chip_selector_pin = 10;
File data_file;

JSONVar json_object;

// Method to write data to SD card
void SDWrite(){
  data_file = SD.open("sensors.txt", FILE_WRITE);
  if (SD.exists("sensors.txt")) {
    Serial.println("File exist for data writing");

    // Print data to the SD card
    data_file.print("Roll: ");
    data_file.print(roll);
    data_file.print(" degree,");
    data_file.print(" Pitch: ");
    data_file.print(pitch);
    data_file.print(" degree,");
    data_file.print(" Smoke: ");
    data_file.print(smoke_value);
    data_file.print("%,");
    data_file.print(" Alcohol: ");
    data_file.print(alcohol_value);
    data_file.print("%,");
    data_file.print(" Vibration: ");
    data_file.print(vibration_value);
    data_file.println("%");


    // Print data to the serial monitor to visualize them
    Serial.print("Roll: ");
    Serial.print(roll);
    Serial.print(" degree,");
    Serial.print(" Pitch: ");
    Serial.print(pitch);
    Serial.print(" degree,");
    Serial.print(" Smoke: ");
    Serial.print(smoke_value);
    Serial.print("%,");
    Serial.print(" Alcohol: ");
    Serial.print(alcohol_value);
    Serial.print("%,");
    Serial.print(" Vibration: ");
    Serial.print(vibration_value);
    Serial.println("%");

    data_file.println(data);
    data_file.close(); 
  }else{
    Serial.println("File not exist for data writing");
  }
}

// Method to read sensor data and store in memory card
void storeDataInMemory(){
  getGyroData();
  smoke_value = analogSensor(smoke_pin);
  alcohol_value = analogSensor(alcohol_pin);
  vibration_value = analogSensor(vibration_pin);
  SDWrite();
}