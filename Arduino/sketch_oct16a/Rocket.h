#include "VGAX.h"

class Rocket
{
  private:
  int temp=0;
  
  bool alive = true;

  public:
  short positionY = 52;
  int position;
  void Clear()//żeby nie VGAX::clear(0) bo czyści cały ekran i kurwa mruga, maluje tam gdzie była rakieta czarny po czym maluje rakiete
  {
    VGAX::fillrect(temp-1, 52, 3, 6, 0);
    //lotki
    VGAX::fillrect(temp-3, 55, 1, 4, 0);
    VGAX::fillrect(temp-2, 56, 1, 3, 0);//czerwone
    VGAX::fillrect(temp+3, 55, 1, 4, 0);
    VGAX::fillrect(temp+2, 56, 1, 3, 0);//czerwone
  }

  void Die(){
    alive = false;
  }

  bool IsAlive(){
    return alive;
  }
  
  void Draw ()
  {
    if(alive){
      position = (analogRead(A2) * 0.1031f)+7;
      if(temp!=position)
      {
      //VGAX::clear(0);  
      Clear();
      //cialo
      VGAX::fillrect(position-1, 52, 3, 6, 3);
      //lotki
      VGAX::fillrect(position-3, 55, 1, 4, 3);
      VGAX::fillrect(position-2, 56, 1, 3, 1);//czerwone
      VGAX::fillrect(position+3, 55, 1, 4, 3);
      VGAX::fillrect(position+2, 56, 1, 3, 1);//czerwone
      temp=position;
      }
    }
  }

  bool CollidesWith(int obstaclePos)
  {
    return position >= obstaclePos - 2 && position <= obstaclePos + 2;
  }
};
