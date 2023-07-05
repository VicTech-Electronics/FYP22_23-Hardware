#include <stdint.h>

// Definition of pin connections
const uint8_t flex1_pin=A2, flex2_pin=A3, flex3_pin=A4, flex4_pin=A5;

// Decralation of useful variables
bool check_value;
bool check_data[4];
uint8_t flex_values[4];
bool A[] = {true, true, true, true};
bool B[] = {false, false, false, false};
bool H[] = {false, false, true, true};
bool I[] = {true, true, true, false};
bool del[] = {true, false, false, true};
bool sound[] = {false, true, true, true};

bool current_reading[4];
char character;

// Other variables
uint8_t max_allowed_error = 3;


bool equalArray(bool arr1[], bool arr2[], int size) {
  for (byte i=0; i < size; i++) {
    if (arr1[i] != arr2[i]) {
      return false;
    }
  }
  return true;
}

// Method to read sensor values
void readSensors(){
  flex_values[0] = (int)map(analogRead(flex1_pin), 0, 1023, 0, 255);
  flex_values[1] = (int)map(analogRead(flex2_pin), 0, 1023, 0, 255);
  flex_values[2] = (int)map(analogRead(flex3_pin), 0, 1023, 0, 255);
  flex_values[3] = (int)map(analogRead(flex4_pin), 0, 1023, 0, 255);
}

char getCharacter(){
  readSensors();
  Serial.print("Reading: ");
  for(byte i=0; i<4; i++){
    if(flex_values[i] < 100) current_reading[i] = true;
    else current_reading[i] = false;
    Serial.print(current_reading[i]);
  }
  Serial.println();
  

  if(equalArray(current_reading, A, 4)) return 'A';
  else if(equalArray(current_reading, B, 4)) return 'B';
  else if(equalArray(current_reading, H, 4)) return 'H';
  else if(equalArray(current_reading, I, 4)) return 'I';
  else if(equalArray(current_reading, del, 4)) return '-';
  else return ' ';
}


// Method to play sound
byte playSound(){
  readSensors();
  Serial.print("Reading: ");
  for(byte i=0; i<4; i++){
    if(flex_values[i] < 100) current_reading[i] = true;
    else current_reading[i] = false;
    Serial.print(current_reading[i]);
  }
  Serial.println();
  

  if(equalArray(current_reading, sound, 4)) return 1;
  else return 0;
}