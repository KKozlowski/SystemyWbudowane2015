#include <EEPROM.h>

void setup()
{
    //26 sounds in a line
    int furElise[] = {329,311,329,311,329,246,293,261,220,146,174,220,247,174,233,247,261,329,311,329,311,329,247,293,261,220, //line 86 https://gist.github.com/spara/1832855
                      147,174,220,247,174,261,247,220,247,261,294,330,196,350,329,294,165,330,294,261, 0}; //line 146
    byte beats[] = {16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8, 32, 32, 64, 12, 80}; 
    int size = 17;
    int i;
    for (i = 0; i < 17; ++i)
      EEPROM.write(i, beats[i]);
    for (i = 0; i < 27;++i)
      EEPROM.write(i + 17, furElise[i]);
}

void loop(){}
