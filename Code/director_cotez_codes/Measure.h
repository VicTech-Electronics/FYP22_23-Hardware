// Definition of pin connection
const uint8_t sensor_pin = A3, load_pin=7;

// Decralation of useful variables
float mVolt_per_amp = 185.0;
float calibiration_value = 0.08;
float unit_price = 200.0;
float kWh, units_addr = 0;

// Methodes
float get_VPP(){
  float reading_value;
  float max_value = 0;
  float min_value = 1023;

  unsigned long start_time = millis();
  while(millis() - start_time < 1000){
    reading_value = analogRead(sensor_pin);
    if(reading_value > max_value) max_value = reading_value;
    else if(reading_value < min_value) min_value = reading_value;
  }
  return (((max_value - min_value) * 5.0) / 1023.0);
}

float get_Irms(){
  float Vrms = (get_VPP() / 2.0) * 0.707;
  return ((Vrms * 1000.0) / mVolt_per_amp) - calibiration_value;
}
