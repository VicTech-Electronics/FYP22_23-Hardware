#include <Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050

int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;
double Acc_x, Acc_y, Acc_z;
double Gyro_x, Gyro_y, Gyro_z;
double roll, pitch;

// Definition of pin connections
const uint8_t flame_pin=A0, smoke_pin=A1, vibration_pin=A2, brake_pin=A3;

// Decralation of useful variables
float smokeCalVal, vibrationCalVal;

// Definition of maximum allowed error
float smokeMaxError=20, vibrationMaxError=20;


//Method to read Gyroscopic data
void getGyroData() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers

  // Read accelerometer and gyroscope data
  accelerometer_x = Wire.read()<<8|Wire.read();
  accelerometer_y = Wire.read()<<8|Wire.read();
  accelerometer_z = Wire.read()<<8|Wire.read();
  int temperature = Wire.read()<<8|Wire.read();
  gyro_x = Wire.read()<<8|Wire.read();
  gyro_y = Wire.read()<<8|Wire.read();
  gyro_z = Wire.read()<<8|Wire.read();

  // Convert raw accelerometer and gyroscope data to meaningful values
  Acc_x = accelerometer_x/16384.0; // sensitivity scale factor for 2g range
  Acc_y = accelerometer_y/16384.0;
  Acc_z = accelerometer_z/16384.0;
  Gyro_x = gyro_x/131.0; // sensitivity scale factor for 250 degrees/s range
  Gyro_y = gyro_y/131.0;
  Gyro_z = gyro_z/131.0;

  // Calculate roll and pitch angles
  roll = abs(atan(Acc_y / sqrt(pow(Acc_x, 2) + pow(Acc_z, 2))) * (180.0 / PI));
  pitch = abs(atan(-Acc_x / sqrt(pow(Acc_y, 2) + pow(Acc_z, 2))) * (180.0 / PI));
}

// Methode to read sensor value in percentage for analog sensor
float analogSensor(uint8_t pin){
  float reading = analogRead(pin);
  return map(reading, 0, 1023, 0, 100);
}

// Method to approximate accident
bool checkAccident(){
  getGyroData();
  if( roll >= 30 || pitch > 30 || 
      // digitalRead(flame_pin) == HIGH || 
      // digitalRead(brake_pin) == HIGH || 
      abs(analogSensor(smoke_pin) - smokeCalVal) >= smokeMaxError || 
      abs(analogSensor(vibration_pin) - vibrationCalVal) >= vibrationMaxError
    ){
      Serial.println("Return true");
      return true;
    }
  else{
    Serial.println("Return false");
    return false;
  }
}