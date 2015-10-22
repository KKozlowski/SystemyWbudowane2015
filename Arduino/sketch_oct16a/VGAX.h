/*
120x60px VGA framebuffer with 4 colors
*/
#ifndef __VGAX_library__
#define __VGAX_library__

#ifdef ARDUINO
#include <Arduino.h>
#endif
#include <avr/pgmspace.h>

#define VGAX_HEIGHT 60 //number of lines
#define VGAX_BWIDTH 30 //number of bytes in a row
#define VGAX_WIDTH (VGAX_BWIDTH*4) //number of pixels in a row
#define VGAX_BSIZE (VGAX_BWIDTH*VGAX_HEIGHT) //size of framebuffer in bytes
#define VGAX_SIZE (VGAX_WIDTH*VGAX_HEIGHT) //size of framebuffer in pixels

//framebuffer. if you want you can write directly to this array. its safe
extern byte vgaxfb[VGAX_HEIGHT*VGAX_BWIDTH];

//clock replacement. this is increment in the VSYNC interrupt, so run at 60Hz
extern unsigned vtimer;

//VGAX class. This is a static class. Multiple instances will not work
class VGAX {
public:

  static void begin(bool enableTone=true);
  static void end();
  static void clear(byte color);

  static inline void putpixel(byte x, byte y, byte color);
  static void fillrect(byte x, byte y, byte width, byte height, byte color);

  static void delay(int msec);
  static inline unsigned millis() { return vtimer*16; }
  static inline unsigned long micros() { return vtimer*16000; }

  static inline void tone(unsigned int frequency);
  static void noTone();
};
#endif
