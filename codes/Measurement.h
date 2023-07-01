#include <Wire.h>

// Definition of useful pins
const uint8_t pressure_pin=A2, value_pin=8;

const int pressureZero = 102.4; //analog reading of pressure transducer at 0psi
const int pressureMax = 921.6; //analog reading of pressure transducer at 100psi
const int pressuretransducermaxPSI = 100; //psi value of transducer being used
const int baudRate = 9600; //constant integer to set the baud rate for serial monitor
const int sensorreadDelay = 250; //constant integer to set the sensor read delay in milliseconds

// Decralation of useful variables
float initial_pressure;

float getPressure(){
  float reading = analogRead(pressure_pin);
  return ((reading-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero);
}

// Methode to calculate pressure used
float getPressureUsed(){
  float used_pressure = initial_pressure - getPressure();
  initial_pressure = getPressure();
  return used_pressure;
}