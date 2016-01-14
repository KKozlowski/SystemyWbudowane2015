#include <EEPROM.h>
#include "VGAX.h"
#include "Game.h"
#include "Audio.h"

Game game;
Audio au;

void setup() {
  game.Begin();
  pinMode(13, INPUT);

  digitalWrite(11, HIGH);
  pinMode(11, OUTPUT);
}

int loopMaxOffset = 10;

void loop()
{
  game.Draw();
  au.Update();
  if(!game.rocket.IsAlive())
    au.stroke();
}

