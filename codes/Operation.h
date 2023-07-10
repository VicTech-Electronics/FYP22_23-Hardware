// Definition of pin connection
const uint8_t dir_pin=9, step_pin=10,
              turbidity_pin=A1, ir1_pin=A2, ir2_pin=A3;

float round_to_dp( float in_value, int decimal_place ){
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

float readTurbidity(){
  float volt = 0.0, ntu = 0.0; 
  for(int i=0; i<800; i++){
    volt += ((float)analogRead(turbidity_pin)/1023)*5;
  }

  volt = volt/800;
  volt = round_to_dp(volt, 2);

  if(volt < 2.5) ntu = 3000;
  else ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 

  return ntu;
}

// Method to rotate converyer
void converyerRotate(){
  digitalWrite(step_pin, HIGH);
  delayMicroseconds(500);
  digitalWrite(step_pin, LOW);
  delayMicroseconds(500);
}


// Method to control the whole operation
void operation(){
  if(digitalRead(ir1_pin) == LOW){
    while(true){
      converyerRotate();
      if(digitalRead(ir2_pin) == LOW) break;
    }

    float turbidity_value = readTurbidity();
    Serial.println(turbidity_value);
  }
}