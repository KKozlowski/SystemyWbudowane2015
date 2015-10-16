#include <VGAX.h>
#include "Rocket.h"
#include "Margins.h"
int a=0;
class Game
{
  public:
  Rocket rocket;
  Margins margins;
  void Begin(){
  VGAX::begin();
  VGAX::clear(0);
  }
  void Draw ()
  {
  rocket.Draw();
  margins.Draw();
  }
};
