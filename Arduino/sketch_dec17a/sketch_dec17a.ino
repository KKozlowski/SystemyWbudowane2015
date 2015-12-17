#include <EEPROM.h>

void setup()
{
    int furElise[] = {329,311,329,311,329,246,293,261,220, 146,174,220,247,174,233,247,261,329,311,329,311,329,247,293,261,220,0};
    byte beats[] = {16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8, 32, 32, 64, 12, 80}; 
    int size = 17;
    int i;
    for (i = 0; i < 17; ++i)
      EEPROM.write(i, beats[i]);
    for (i = 0; i < 27;++i)
      EEPROM.write(i + 17, furElise[i]);
}

void loop(){}
