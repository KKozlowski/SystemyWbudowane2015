#include <EEPROM.h>

void setup()
{
    byte furElise[] = {33,31,33,31,33,25,29,26,22,15,17,22,25,17,23,25,26,33,31,33,31,33,25,29,26,22, //line 86 https://gist.github.com/spara/1832855
                      15,17,22,25,17,26,25,22,25,26,29,33,20,35,33,29,17,33,29,26, 0}; //line 15
    byte beats[] = {16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8, 32, 32, 64, 12, 80}; 
    int size = 17;
    int i;
    for (i = 0; i < 17; ++i)
      EEPROM.write(i, beats[i]);
    for (i = 0; i < 47;++i)
      EEPROM.write(i + 17, furElise[i]);
}

void loop(){}
