class Sensor{
  public:
    uint8_t sensor_pin;
    Sensor(uint8_t pin){
      sensor_pin = pin;
    }

    
    float calibiration(){
      float calibiration_value = 0.0;
      for(byte i=0; i<100; i++){
        calibiration_value += analogRead(sensor_pin);
      }
      return calibiration_value /= 100;
    }

    float getValue(){
      float sensor_value = 0.0;
      for(byte i=0; i<100; i++){
        sensor_value += analogRead(sensor_pin);
      }
      return sensor_value /= 100;
    }
};