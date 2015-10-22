#include "VGAX.h"

#define delay 10;
#define size 12;
class Audio
{
  private:
  static int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 }; 
  static byte counter = 0;
  static byte index = 0;

  public:
  static void Update()
  {
    ++counter %= delay;
    
    if (!counter)
    {
      VGAX::tone(beats[index]);
      ++index %= size;
    }
  }
}

