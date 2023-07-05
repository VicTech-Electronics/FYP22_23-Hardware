#include "Player.h"
#include "Reading.h"
#include "Interface.h"

// Decralation of usefull variables
String string_to_print = "";
char char_to_print, previous_char;

// Method to run complete operations
void operation(){
  byte sound_index_to_play = playSound();
  if(sound_index_to_play == 0){
    char_to_print = getCharacter();
    Serial.println("Obtained char: " + String(char_to_print));
    Serial.println("String to print: " + string_to_print);
    if(char_to_print != previous_char){
      if(char_to_print == '-') {
        string_to_print = "";
        lcdPrint("Hand talk", "System");
      }else if(char_to_print != ' '){
        string_to_print += String(char_to_print);
        lcdPrint(string_to_print, "");
      }
      previous_char = char_to_print;
    }
  }else{
    lcdPrint("Hand talk", "System");
    playSound(sound_index_to_play);
  }
}