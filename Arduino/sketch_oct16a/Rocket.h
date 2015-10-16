#include <VGAX.h>

class Rocket
{
  private:
  
  int position;

  public:
  
  void Draw ()
  {
    position = analogRead(A2)/8.5333f;

    //cialo
    VGAX::fillrect(position-1, 4, 3, 5, 3);
    //lotki
    VGAX::fillrect(position-2, 2, 1, 2, 3);
    VGAX::fillrect(position-3, 2, 1, 2, 3);
    //glowica
    VGAX::putpixel(position, 5, 3);
  }

  bool CollidesWith(int obstaclePos)
  {
    return position >= obstaclePos - 1 && position <= obstaclePos + 1;
  }
};
