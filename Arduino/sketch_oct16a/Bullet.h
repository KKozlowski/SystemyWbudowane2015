#include "VGAX.h"
class Bullet {
  private:
  byte counter;
  
  public:
  bool enabled;
  int posX, posY;

  void ClearBehind(){
    VGAX::fillrect(posX, posY+3, 1, 3, 0);
  }
  
  void Draw(){
    counter = (counter+1)%10;
    
    if (!counter)
    {
      
      posY-=3;
      
      VGAX::fillrect(posX, posY, 1, 3, 2);
      ClearBehind();
    }
   
  }

  void Destroy(){
    VGAX::fillrect(posX, posY, 1, 3, 0);
    enabled = false;
  }

  void Spawn(int x, int y){
    enabled = true;
    posX = x;
    posY = y;
  }
};

