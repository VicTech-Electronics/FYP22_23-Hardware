#include <stdint.h>

// Definition of pin connections
const uint8_t flex1_pin=A2, flex2_pin=A3, flex3_pin=A4, flex4_pin=A5;

// Decralation of useful variables
bool check_value;
bool check_data[4];
uint8_t flex_values[4];
uint8_t A[] = {12, 133, 3, 34};
uint8_t B[] = {12, 133, 3, 34};
uint8_t C[] = {12, 133, 3, 34};
uint8_t D[] = {12, 133, 3, 34};
uint8_t E[] = {12, 133, 3, 34};
uint8_t F[] = {12, 133, 3, 34};
uint8_t G[] = {12, 133, 3, 34};
uint8_t H[] = {12, 133, 3, 34};
uint8_t I[] = {12, 133, 3, 34};
uint8_t J[] = {12, 133, 3, 34};
uint8_t K[] = {12, 133, 3, 34};
uint8_t L[] = {12, 133, 3, 34};
uint8_t M[] = {12, 133, 3, 34};
uint8_t N[] = {12, 133, 3, 34};
uint8_t O[] = {12, 133, 3, 34};
uint8_t P[] = {12, 133, 3, 34};
uint8_t Q[] = {12, 133, 3, 34};
uint8_t R[] = {12, 133, 3, 34};
uint8_t S[] = {12, 133, 3, 34};
uint8_t T[] = {12, 133, 3, 34};
uint8_t U[] = {12, 133, 3, 34};
uint8_t V[] = {12, 133, 3, 34};
uint8_t W[] = {12, 133, 3, 34};
uint8_t X[] = {12, 133, 3, 34};
uint8_t Y[] = {12, 133, 3, 34};
uint8_t Z[] = {12, 133, 3, 34};
uint8_t space[] = {12, 133, 3, 34};
uint8_t del[] = {12, 133, 3, 34};

uint8_t* alphabet[] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, space, del};
char character[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '-'};

// Other variables
uint8_t max_allowed_error = 3;

// Method to read sensor values
void readSensors(){
  flex_values[0] = (int)map(analogRead(flex1_pin), 0, 1023, 0, 255);
  flex_values[1] = (int)map(analogRead(flex2_pin), 0, 1023, 0, 255);
  flex_values[2] = (int)map(analogRead(flex3_pin), 0, 1023, 0, 255);
  flex_values[3] = (int)map(analogRead(flex4_pin), 0, 1023, 0, 255);
}

char getCharacter(){
  for(byte i=0; i<28; i++){ // Loop across the alphabet arrays
    uint8_t* current_alphabet = alphabet[i];
    for(byte j=0; j<4; j++){ // Check the individual data
      if(abs(flex_values[j] - current_alphabet[j]) <= max_allowed_error) check_data[j] = true;
      else check_data[j] = false;
    }

    for(byte k=0; k<4; k++){
      if(check_data[k] == false){
        check_value = false;
        break;
      }else check_value = true;
    }

    if(check_value) return character[i];
  } return '0';
}


// Check sounds
uint8_t sound1[] = {12, 133, 3, 34};
uint8_t sound2[] = {12, 133, 3, 34};
uint8_t sound3[] = {12, 133, 3, 34};
uint8_t sound4[] = {12, 133, 3, 34};
uint8_t sound5[] = {12, 133, 3, 34};

uint8_t* sound[] = {sound1, sound2, sound3, sound4, sound5};

// Method to play sound
byte playSound(){
  for(byte i=0; i<5; i++){ // Loop across the alphabet arrays
    uint8_t* current_sound = sound[i];
    for(byte j=0; j<4; j++){ // Check the individual data
      if(abs(flex_values[j] - current_sound[j]) <= max_allowed_error) check_data[j] = true;
      else check_data[j] = false;
    }

    for(byte k=0; k<4; k++){
      if(check_data[k] == false){
        check_value = false;
        break;
      }else check_value = true;
    }

    if(check_value) return i+1;
  } return 0;
}