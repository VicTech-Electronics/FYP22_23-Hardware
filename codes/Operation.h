#include "Player.h"
#include "Reading.h"
#include "Interface.h"


// Method to run complete operations
void operation(){
  byte sound_index_to_play = playSound();
  if(sound_index_to_play == 0){
    String string_to_print = "";
    char char_to_print, previous_char;
    while(true){
      char_to_print = getCharacter();
      if(char_to_print != previous_char){
        if(char_to_print != '0'){
          string_to_print += String(char_to_print);
          lcdPrint(string_to_print, "");
        }
        if(char_to_print == '-') {
          lcdPrint("Hand talk", "System");
          break;
        }
        previous_char = char_to_print;
      }
    }
  }else{
    lcdPrint("Hand talk", "System");
    playSound(sound_index_to_play);
  }
}