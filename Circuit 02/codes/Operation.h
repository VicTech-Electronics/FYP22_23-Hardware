// Definition of pin connection
const uint8_t pump1_pin=A1, pump2_pin=A2, sensor_pin=A3;

// Method to fill reseve tank
void saveReserve(String state){
  if(state == "fill"){
    digitalWrite(pump1_pin, HIGH);
    digitalWrite(pump2_pin, LOW);
  }else if(state == "supply"){
    digitalWrite(pump1_pin, LOW);
    digitalWrite(pump2_pin, HIGH);
  }else{
    digitalWrite(pump1_pin, LOW);
    digitalWrite(pump2_pin, LOW);
  }
}

// Control operation start here
void operation(){
  if(receiveNRF == "Empty" &&  digitalRead(sensor_pin) == LOW) saveReserve("supply");
  else if(receiveNRF == "Full" &&  digitalRead(sensor_pin) == HIGH) saveReserve("fill");
  else saveReserve("stop");
}
