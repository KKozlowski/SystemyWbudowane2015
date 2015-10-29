#include "VGAX.h"

class Obstacle {
  private:
  byte counter;
  public:
  byte posX;
  byte posY;
  bool enabled;

  void ClearBehind()
  {
    VGAX::fillrect(posX-2, posY-2, 5, 2, 0);
  }

  void ClearAll(){
    VGAX::fillrect(posX-2, posY-2, 5, 5, 0);
  }

  void Draw()
  {  
    counter = (counter+1)%10;
    
    if (!counter)
    {
      ClearBehind();
      ++posY;
      
      VGAX::fillrect(posX-2, posY-1, 5, 3, 1);
      VGAX::fillrect(posX-1, posY-2, 3, 5, 1);
    }
  }

  void Activate()
  {
    enabled = true;
    posY = 3;
    posX = random(10, 110);
    counter = 0;
  }
  void Destroy(){
    ClearAll();
    enabled= false;
    posY=64;
  }
};

