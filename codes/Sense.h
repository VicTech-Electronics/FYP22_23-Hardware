// Definition of pin connection
cons t uint8_t sensorPins[] = {A0, A1, A2, A3, A4};
float calibirationValues[] = {0.0, 0.0, 0.0, 0.0, 0.0};
float sensorValues[] = {0.0, 0.0, 0.0, 0.0, 0.0};
bool packingStatus[] = {false, false, false};

// Methode to calibirate LDR sensor
void calibration(){
  for(byte i=0; i<100; i++)
    for(byte i=0; i<5; i++)
      calibirationValues[i] += analogRead(sensorPins[i]);

  for(byte i=0; i<5; i++)
   calibirationValues[i] /= 100;
}

// Method to read sensor values
void getSensor(){
  for(byte i=0; i<5; i++)
    sensorValues[i] = analogRead(sensorPins[i]);
}