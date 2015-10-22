#include "VGAX.h"

#define delay 50;
#define size 12;
class Audio
{
  private:
  static int beats[size]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 }; 
  static byte counter = 0;
  static byte index = 0;

  public:

  static void Init()
  {
    counter = 0;
    index = 0;

    beats[0] = 16;
    beats[1] = 16;
    beats[2] = 16;
    beats[3] = 8;
    beats[4] = 8;
    beats[5] = 16;
    beats[6] = 32;
    beats[7] = 16;
    beats[8] = 16;
    beats[9] = 16;
    beats[10] = 8;
    beats[11] = 8;
  }
  
  static void Update()
  {
    ++counter %= delay;
    
    if (!counter)
    {
      VGAX::tone(beats[index]);
      ++index %= size;
    }
  }
};

