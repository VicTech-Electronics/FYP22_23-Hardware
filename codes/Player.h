#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial serialDFPlayer(10, 11); // RX, TX
DFRobotDFPlayerMini DFPlayer;

// Method to play a sound
void playSound(byte sound_index){
  DFPlayer.playMp3Folder(sound_index);
  delay(3e3);
}
