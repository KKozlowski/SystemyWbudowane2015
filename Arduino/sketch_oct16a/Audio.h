#include <EEPROM.h>
#include "VGAX.h"

#define delay 50;
#define size 17;
class Audio
{
  private:
  //int beats[12]; 
  byte counter = 0;
  byte index = 0;
  byte beats[17] = {16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8, 32, 32, 64, 12, 80}; 

  public:
  Audio(){
  }
  
  void Update()
  { 
    //int furElise[] = {329,311,329,311,329,246,293,261,220, 146,174,220,247,174,233,247,261,329,311,329,311,329,247,293,261,220,0};
    byte beats[] = {16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8, 32, 32, 64, 12, 80}; 
  
    
    ++counter %= delay;
    
    if (!counter)
    {
      VGAX::tone(beats[index]*10);
      ++index %= sizeof(beats);
    } 
  }
   /* void Update()
  { 
    
    if (!counter)
    {
      VGAX::tone(EEPROM[index]*10);
      ++index %= 17;
    }
  }*/
};

