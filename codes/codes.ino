/*
  VicTech Electronics
  Frank Project
  Mbegani (Bagamoyo)
  FYP2022/23
  VTE37
*/

// Definition of pin connection
const uint8_t ind_pin=7, pump_pin=9, sensor_pin=8;

void setup() {
  pinMode(ind_pin, OUTPUT);
  pinMode(pump_pin, OUTPUT);
  pinMode(sensor_pin, INPUT);

  Serial.begin(9600);
}

void loop() {
  if(digitalRead(sensor_pin) == LOW){
    digitalWrite(ind_pin, HIGH);
    digitalWrite(pump_pin, HIGH);
  }else(
    digitalWrite(ind_pin, HIGH);
    digitalWrite(pump_pin, HIGH);
  )
}
