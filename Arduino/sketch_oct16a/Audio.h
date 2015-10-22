#include "VGAX.h"

#define delay 50;
#define size 17;
class Audio
{
  private:
  //int beats[12]; 
  byte counter = 0;
  byte index = 0;

  public:
  Audio(){
  }
  
  void Update()
  {
    int beats[] = {160, 160, 160,  80,  80,  160, 320, 160, 160, 160, 80, 80, 320, 320, 640, 120, 800}; 
    ++counter %= delay;
    
    if (!counter)
    {
      VGAX::tone(beats[index]);
      ++index %= sizeof(beats)/2;
    } 
  }
};

