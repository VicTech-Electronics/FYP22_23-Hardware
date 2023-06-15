#include "DataFile.h"
void setup(){
  pinMode(flame_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);

  Serial.begin(9600);

  Wire.begin(); // Initialize the I2C library
  Wire.beginTransmission(MPU_addr); // Start communication with MPU6050
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // Wake up the MPU6050
  Wire.endTransmission(true);

  // Initialize SD card
  if (!SD.begin(chip_selector_pin)) {
    Serial.println("SD card initialization failed!");
    while (true);
  } Serial.println("SD card initialization SUCCESS");
}

void loop() {
  readData();
  while(serialESP.available()){
    String serial_data = serialESP.readString();
    Serial.println(serial_data);
  }
}