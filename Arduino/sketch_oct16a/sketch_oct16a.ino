#include "VGAX.h"
#include "Game.h"


Game game;

void setup() {
  game.Begin();
   }

//768 - F#
//447 - A
//300 - D
int loopMaxOffset = 10;

void loop()
{
  //VGAX::tone(726);
  game.Draw();

  static unsigned cnt;
  if (!(cnt % 10))
    VGAX::noTone();
  if (!(cnt++%20))
    VGAX::tone(cnt*5+11);
  if (cnt>=120 + loopMaxOffset%120){
    cnt=0;
    loopMaxOffset +=10;
  }
}

