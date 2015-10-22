#include "VGAX.h"

class Obstacle {
  public:
  int posX;
  int posY = 3;


  
  Obstacle(int x){
    posX = x;
  }

  void Draw(){
    VGAX::fillrect(posX-2, posY-1, 5, 3, 1);
    VGAX::fillrect(posX-1, posY-2, 3, 5, 1);
  }
};

