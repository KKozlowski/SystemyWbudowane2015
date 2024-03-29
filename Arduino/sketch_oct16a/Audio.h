#include <EEPROM.h>
#include "VGAX.h"

#define delay 50
#define sizez 17
#define eliseSize 47
class Audio
{
  private:
  byte counter = 0;
  byte index = 0;
  int offset;
  int leng;
  int soundLength;
  int toneHigh = 12;
  bool stroked = false;
  public:
  Audio(){
    offset = sizez;
    leng = eliseSize;
    soundLength = delay;
  }
  
  void stroke(){
    if (stroked) return;
    else{
      stroked = true;
      counter = 0;
      index = 0;
      offset = 0;
      leng = sizez;
      toneHigh = 10;
      soundLength = 2*delay;
    }
  }
  
  void Update()
  {
      ++counter %= soundLength;
      if (!counter)
      {
        int ton = EEPROM[index+offset];
        ton*=toneHigh;
        VGAX::tone(ton);
        ++index %= leng;
      }
    
  }
};

