#include "VGAX.h"

class Obstacle {
  private:
  int realPosY;
  public:
  int posX;
  int posY = 3;


  
  Obstacle(int x){
    posX = x;
  }

  void ClearBehind(){
    VGAX::fillrect(posX-2, posY-2, 5, 2, 0);
  }

  void Draw(){
    
    realPosY++;
    if (realPosY/10 != posY){
      ClearBehind();
      posY = realPosY/10;
      
      VGAX::fillrect(posX-2, posY-1, 5, 3, 1);
      VGAX::fillrect(posX-1, posY-2, 3, 5, 1);
    }
  }
};

