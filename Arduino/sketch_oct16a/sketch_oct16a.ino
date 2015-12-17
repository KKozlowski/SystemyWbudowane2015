#include <EEPROM.h>
#include "VGAX.h"
#include "Game.h"
#include "Audio.h"

Game game;
Audio au;

void setup() {
  game.Begin();
  pinMode(13, INPUT);
  
   }

//768 - F#
//447 - A
//300 - D
int loopMaxOffset = 10;

void loop()
{
  //VGAX::tone(726);
  game.Draw();
  au.Update();
  //VGAX::clear(1);
  //delay(100000);
  //digitalWrite(11, LOW);
  /*static unsigned cnt;
  if (!(cnt % 10))
    VGAX::noTone();
  if (!(cnt++%20))
    VGAX::tone(cnt*5+11);
  if (cnt>=120 + loopMaxOffset%120){
    cnt=0;
    loopMaxOffset +=10;
  }*/
}

