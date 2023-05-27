#include <DHT.h>
#define dht_pin A5
#define dht_type DHT11

DHT dht(dht_pin, dht_type);

struct dhtStruct{
  float temperature;
  float humidity;
};

dhtStruct dhtValues;

dhtStruct getTemperatureAndHumidity(){
  dhtValues.temperature = dht.readTemperature();
  dhtValues.humidity = dht.readHumidity();

  if(isnan(dhtValues.temperature) || isnan(dhtValues.humidity)){
    Serial.println("Fail to read temperature and Humidity");
    lcdPrint("Error:", "DHT fail");
    dhtValues.temperature = -1;
    dhtValues.humidity = -1;
    return dhtValues;
  }else{
    return dhtValues;
  }
}