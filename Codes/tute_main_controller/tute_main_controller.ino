#include "DataFile.h"

// Decrlation of useful variable
unsigned long initial_time;

void setup(){
  pinMode(flame_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);

  Serial.begin(9600);
  serialESP.begin(9600);

  Wire.begin(); // Initialize the I2C library
  Wire.beginTransmission(MPU_addr); // Start communication with MPU6050
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // Wake up the MPU6050
  Wire.endTransmission(true);
  delay(3e3);

  // Initialize SD card
  if (!SD.begin(chip_selector_pin)) {
    Serial.println("SD card initialization failed!");
    // while (true);
  } Serial.println("SD card initialization SUCCESS");

  initial_time = millis();
}

void loop() {
  if(millis() - initial_time > 5000){
    storeDataInMemory();
    initial_time = millis();
  }
  
  if(roll > 45 || pitch > 45 ||
    vibration_value >= 50 ||
    smoke_value >= 50 ||
    digitalRead(flame_pin) ==HIGH
  ){
    getLocation();
    Serial.println("Send data");
    data = "{\"vehicle_number\": \"" + vehicle_number + "\"";
    data += ",\"latitude\": " + String(latitude, 5);
    data += ",\"longitude\": " + String(longitude, 5);
    data += ",\"description\": \"Readings\"}";
    
    Serial.println("Data to send: " + data);
    serialESP.println(data);
    while(!serialESP.available());
    data = serialESP.readString();
    Serial.println(data);
  }
}