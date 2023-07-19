/*
 * VicTech Electronics
 * VictoniX project
 * FYP2022/23
 * VTE__
 */

# include "Communication.h"

void setup() {
  pinMode(serial_interrupt_pin, OUTPUT);
  pinMode(confirm_BTN, INPUT_PULLUP);
  pinMode(cancel_BTN, INPUT_PULLUP);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(brake_pin, INPUT);
  pinMode(flame_pin, INPUT);

  Wire.begin(); // Initialize the I2C library
  Wire.beginTransmission(MPU_addr); // Start communication with MPU6050
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // Wake up the MPU6050
  Wire.endTransmission(true);

  Serial.begin(9600);
  serialESP.begin(9600);

  delay(10e3);

  // Calculate the calibration for analog sensors
  smokeCalVal=0.0; vibrationCalVal=0.0;
  for(byte i=0; i<100; i++){
    smokeCalVal += analogSensor(smoke_pin);
    vibrationCalVal += analogSensor(vibration_pin);
  }
  smokeCalVal /= 100;
  vibrationCalVal /= 100;



  Serial.println("Program start");
  digitalWrite(buzzer_pin, HIGH);
  delay(100);
  digitalWrite(buzzer_pin, LOW);

  Serial.println("smokeCal: " + String(smokeCalVal));
  Serial.println("vibrationCal: " + String(vibrationCalVal));

  attachInterrupt(digitalPinToInterrupt(confirm_BTN), confirmISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(cancel_BTN), cancelISR, FALLING);
}

void loop() {
  if(checkAccident()) postAccientData();
  confirmation();
  cancelation();
  delay(100);
}