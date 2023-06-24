class ACS712_sensor {
  private:
  float Vrms;
  float reading_value;
  float mVolt_per_amp = 185.0;
  float calibiration_value = 0.08;
  
  public:
  uint8_t sensor_pin;
  
  ACS712_sensor(uint8_t sensor){
    sensor_pin = sensor;
  }

  
  float get_VPP(){
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
    Vrms = (get_VPP() / 2.0) * 0.707;
    return ((Vrms * 1000.0) / mVolt_per_amp) - calibiration_value;
  }
};
