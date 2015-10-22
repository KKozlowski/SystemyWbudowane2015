#include "VGAX.h"
#include "Rocket.h"
#include "Margins.h"
#include "Obstacle.h"

int a=0;
class Game
{
  public:
  Rocket rocket;
  Margins margins;
  Obstacle *obs[10];
  int maxY;
  
  void Begin(){
  VGAX::begin();
  VGAX::clear(0);
  obs[0] = new Obstacle(50);
  }
  
  void Draw (){
  rocket.Draw();
  margins.Draw();
  obs[0]->Draw();
  //25 - g
  //28 - e
  //
  //VGAX::tone(50);
  }
};
