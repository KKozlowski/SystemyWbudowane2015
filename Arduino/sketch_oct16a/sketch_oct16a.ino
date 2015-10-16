#include <VGAX.h>
#include "Rocket.h"

#define width 120
#define height 60

Rocket rocket;

void Draw()
{
  VGAX::clear(0);

  VGAX::fillrect(0, 0, 1, 60, 2);
  VGAX::fillrect(119, 0, 1, 60, 2);
}

void setup() {}

void loop()
{
  Draw();
  rocket.Draw();
}

