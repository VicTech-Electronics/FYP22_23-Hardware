#include <SoftwareSerial.h>
#define tft_rx 13
#define tft_tx 12

SoftwareSerial serialTFT(tft_rx, tft_tx);

// Method to send data to the TFT display
void sendData(String data){
  serialTFT.print(data); 
  serialTFT.write(0xff);       
  serialTFT.write(0xff);
  serialTFT.write(0xff);
}