#include "Interface.h"
#define LOW_LEVEL "low"
#define MEDIUM_LEVEL "medium"
#define HIGH_LEVEL "high"

// Definitin of pin connections
const uint8_t fan_pin=6, peltier_pin=7, thermistor_pin=A1;

// Parameters for the Steinhart-Hart equation
const float thermistorNominal = 10000.0;  // Thermistor resistance at nominal temperature (in ohms)
const float temperatureNominal = 25.0;    // Nominal temperature for the thermistor (in degrees Celsius)
const float BCoefficient = 3950.0;         // Beta coefficient of the thermistor

// Method for confirmation and cancelation
void confirmation(){
  confirm = true;
}
void cancelation(){
  cancel = true;
}

// Method for temperature providing
void getTemperature(String level){
  if(level=="low"){
    digitalWrite(fan_pin, HIGH);
    digitalWrite(peltier_pin, HIGH);
  }else if(level=="medium"){
    digitalWrite(fan_pin, LOW);
    digitalWrite(peltier_pin, HIGH);
  }else if(level=="low"){
    digitalWrite(fan_pin, LOW);
    digitalWrite(peltier_pin, LOW);
  }
}

// Method to measure temperaure
float measureTemperature(){
  // Read the raw ADC value from the thermistor pin
  int rawADC = analogRead(thermistor_pin);

  // Convert the raw ADC value to resistance
  float resistance = thermistorNominal / (1023.0 / rawADC - 1.0);

  // Calculate the temperature using the Steinhart-Hart equation
  float steinhart;
  steinhart = resistance / thermistorNominal;                  // (R/Ro)
  steinhart = log(steinhart);                                  // ln(R/Ro)
  steinhart /= BCoefficient;                                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (temperatureNominal + 273.15);            // + (1/To)
  steinhart = 1.0 / steinhart;                                 // Invert
  float temperatureValue = steinhart - 273.15;                 // Convert to Celsius

  lcdPrint("Peltier vaccine", "Temp: " + String(temperatureValue) + "C");
  return temperatureValue;
}

// Method to handle operation
void operation(){
  if(measureTemperature() < temperature) getTemperature(HIGH_LEVEL);
  else if(measureTemperature() == temperature) getTemperature(MEDIUM_LEVEL);
  else if(measureTemperature() > temperature) getTemperature(LOW_LEVEL);
}