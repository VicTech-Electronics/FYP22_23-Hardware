// Definition of useful pins
const uint8_t red_pin=6, green_pin=5, buzzer_pin=7;

void alerting(bool is_alert, bool is_danger){
  if(is_alert){
    if(is_danger){
      digitalWrite(red_pin, HIGH);
      digitalWrite(buzzer_pin, HIGH);
    }else{
      digitalWrite(green_pin, HIGH);
    }
  }else{
    digitalWrite(red_pin, LOW);
    digitalWrite(buzzer_pin, LOW);
    digitalWrite(green_pin, LOW);
  }
}
