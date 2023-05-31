#include <PulseSensorPlayground.h>

// Definition of pin connections
const uint8_t hear_rate_pin=2, temp_pin=A1;

PulseSensorPlayground pulseSensor;

// Decralation of usefull variables
const int referenceResistor = 10000; // Resistance value of the reference resistor (in ohms)
const float referenceVoltage = 5.0; // Reference voltage (in volts)

// Method to measerue heart reate
float getHeartRate(){
 if (pulseSensor.sawStartOfBeat()){
   return float(pulseSensor.getBeatsPerMinute());
 }else return -1;
 
}

// Method to measure temperature
float getTemperature(){
  int rawValue = analogRead(temp_pin); // Read analog value from the thermistor pin

  // Calculate the resistance of the thermistor
  float thermistorResistance = referenceResistor * (1023.0 / rawValue - 1.0);

  // Steinhart-Hart equation coefficients for the thermistor
  const float A = 0.001129148;
  const float B = 0.000234125;
  const float C = 0.0000000876741;

  // Calculate temperature in Kelvin
  float temperatureKelvin = 1.0 / (A + B * log(thermistorResistance) + C * pow(log(thermistorResistance), 3));

  // Convert temperature to Celsius
  float temperatureCelsius = temperatureKelvin - 273.15;

  return temperatureCelsius;
}
