//linie pikseli - linie na ekranie LCD
//linie punktow - linie w tablicy pikseli w Arduino

#include "VGAX.h"

//HSYNC pin used by TIMER2
#define HSYNCPIN 3
//These two pin cannot be modified without modify the HSYNC assembler code
#define COLORPIN0 6
#define COLORPIN1 7
//VSYNC pin used by TIMER1. Can be 9 or 10
#define VSYNCPIN 9
//Number of VGA lines to be skipped (black lines)
#define SKIPLINES 90
//number of visible lines, after SKIPLINES
#define RENDERLCOUNT 359

#define POINTTOPIXELHEIGHT 6
#define POINTTOPIXELHEIGHTMINUSONE 5

static byte afreq, //przechowuje częstotliwość aktualnego tonu
            afreq0;//służy do sprawdzania, czy ton jest zerowy
unsigned vtimer;
static byte aline,    //liczy linie pikseli przeznaczone na wyświetlenie jednej linii punktów. Gdy osiągnie 6, rlinecnt jest inkrementowany.
            rlinecnt; //iterator linii punktów. Osiąga wartości od 0 do 60.
static byte vskip; //liczba pomijanych linii pikseli na początku
byte vgaxfb[VGAX_HEIGHT*VGAX_BWIDTH]; //tablica pikseli

ISR(TIMER1_OVF_vect) { //Przejęcie funkcji zegara 1
  aline=-1;
  vskip=SKIPLINES;
  vtimer++;
  rlinecnt=0;
}
ISR(TIMER2_OVF_vect) { //Przejęcie funkcji zegara 2
  /*
  NOTE: I prefer to generate the line here, inside the interrupt.
  Gammon's code generate the line pixels inside main().
  My versin generate the signal using only interrupts, so inside main() function
  you can do anything you want. Your code will be interrupted when VGA signal
  needs to be generated
  */
  //generate audio modulation. around 15 clocks
  asm volatile(                                   //4c to load Z and Y
    "      ld r16, Z                        \n\t" //c1 r16=afreq
    "      cpi %[freq0], 0                  \n\t" //c1 afreq0==0 ?
    "      breq no_audio                    \n\t" //c1/2 *0
    "play_audio:                            \n\t"
    "      cpi r16, 0                       \n\t" //c1 afreq==0 ?
    "      brne dont_flip_audio_pin         \n\t" //c1/2 *1
    "flip_audio_pin:                        \n\t"
    "      ldi r18, 1                       \n\t" //c1
    "      out %[audiopin], r18             \n\t" //c1
    "      st Z, %[freq0]                   \n\t" //c1 afreq=afreq0
    "      rjmp end                         \n\t" //c2
    "no_audio:                              \n\t"
    "      nop                              \n\t" //c1
    "      nop                              \n\t" //c1
    "      nop                              \n\t" //c1
    "      nop                              \n\t" //c1
    "      nop                              \n\t" //c1
    "      nop                              \n\t" //c1
    "      rjmp end                         \n\t" //c2
    "dont_flip_audio_pin:                   \n\t"
    "      dec r16                          \n\t" //c1
    "      st Z, r16                        \n\t" //c1
    "      nop                              \n\t" //c1
    "end:                                   \n\t"
  :
  : "z" (&afreq),
    [freq0] "r" (afreq0),
    [audiopin] "i" _SFR_IO_ADDR(PINC)
  : "r16", "r18");

  //check vertical porch
  if (vskip) {  //najpierw pomija 90 linii
      vskip--;
      return;
  }
  if (rlinecnt<60) {
    //interrupt jitter fix (needed to keep signal stable)
    //code from https://github.com/cnlohr/avrcraft/tree/master/terminal
    //modified from 4 nop align to 8 nop align
    #define DEJITTER_OFFSET 1
    #define DEJITTER_SYNC -3
    asm volatile(
      "     lds r16, %[timer0]    \n\t" //
      "     subi r16, %[tsync]    \n\t" //
      "     andi r16, 7           \n\t" //
      "     call TL               \n\t" //
      "TL:                        \n\t" //
      "     pop r31               \n\t" //
      "     pop r30               \n\t" //
      "     adiw r30, (LW-TL-5)   \n\t" //
      "     add r30, r16          \n\t" //
      "     ijmp                  \n\t" //
      "LW:                        \n\t" //
      "     nop                   \n\t" //
      "     nop                   \n\t" //
      "     nop                   \n\t" //
      "     nop                   \n\t" //
      "     nop                   \n\t" //
      "     nop                   \n\t" //
      "     nop                   \n\t" //
      //"   nop                   \n\t" //
      "LBEND:                     \n\t" //
    :
    : [timer0] "i" (&TCNT0),
      [toffset] "i" ((uint8_t)DEJITTER_OFFSET),
      [tsync] "i" ((uint8_t)DEJITTER_SYNC)
    : "r30", "r31", "r16", "r17");
    /*
    Output all pixels.

    NOTE: My trick here is to unpack 4 pixels and shift them before writing to
    PORTD.

    Pixels are packed as 0b11223344 because the first pixel write have no time
    to perform a shift (ld, out) and must be prealigned to the two upper bits
    of PORTD, where the two wires of the VGA DSUB are connected. The second,
    the third and the forth pixels are shifted left using mul opcode instead
    of a left shift opcode. Shift opcodes are slow and can shift only 1 bit at
    a time, using 1 clock cycle. mul is faster.

    Instead of using a loop i use the .rept assembler directive to generate an
    unrolled loop of 30 iterations.
    */
    asm volatile (
      "    ldi r20, 4       \n\t" //const for <<2bit
      #ifdef VGAX_DEV_DEPRECATED
      ".rept 14             \n\t" //center line
      "    nop              \n\t" //
      ".endr                \n\t" //
      #endif
      ".rept 30             \n\t" //output 4 pixels for each iteration
      "    ld r16, Z+       \n\t" //
      "    out %[port], r16 \n\t" //write pixel 1
      "    mul r16, r20     \n\t" //<<2
      "    out %[port], r0  \n\t" //write pixel 2
      "    mul r0, r20      \n\t" //<<4
      "    out %[port], r0  \n\t" //write pixel 3
      "    mul r0, r20      \n\t" //<<6
      "    out %[port], r0  \n\t" //write pixel 4
      ".endr                \n\t" //
      "    nop              \n\t" //expand last pixel
      "    ldi r16, 0       \n\t" //
      "    out %[port], r16 \n\t" //write black for next pixels
    :
    : [port] "I" (_SFR_IO_ADDR(PORTD)),
      "z" "I" (/*rline*/(byte*)vgaxfb + rlinecnt*VGAX_BWIDTH)
    : "r16", "r17", "r20", "r21", "memory");

    if (++aline==POINTTOPIXELHEIGHTMINUSONE) { //po zużyciu 6 linii pikseli program przechodzi do następnej linii punktów - bufor linii (rlinecnt) jest inkrementowany, zas aline jest resetowany.
      aline=-1;
      rlinecnt++;
    } else {
      #ifdef VGAX_DEV_DEPRECATED
      //small delay to keep the line signal aligned
      asm volatile(
        ".rept 17 \n\t" //
        "    nop  \n\t" //
        ".endr    \n\t" //
      :::);
      #endif
    }
  }
}

void VGAX::begin(bool enableTone) {
  //Timers setup code, modified version of the Nick Gammon's VGA sketch
  cli(); //CLI wyłącza przerwania
  //setup audio pin
  if (enableTone)
    pinMode(A0, OUTPUT);

  //disable TIMER0 interrupt
  TIMSK0=0;
  TCCR0A=0;
  TCCR0B=1; //enable 16MHz counter (used to fix the HSYNC interrupt jitter)
  OCR0A=0;
  OCR0B=0;
  TCNT0=0;
  //TIMER1 - vertical sync pulses
  pinMode(VSYNCPIN, OUTPUT);
  #if VSYNCPIN==10
  TCCR1A=bit(WGM10) | bit(WGM11) | bit(COM1B1);
  TCCR1B=bit(WGM12) | bit(WGM13) | bit(CS12) | bit(CS10); //1024 prescaler
  OCR1A=259; //16666 / 64 uS=260 (less one)
  OCR1B=0; //64 / 64 uS=1 (less one)
  TIFR1=bit(TOV1); //clear overflow flag
  TIMSK1=bit(TOIE1); //interrupt on overflow on TIMER1
  #else
  TCCR1A=bit(WGM11) | bit(COM1A1);
  TCCR1B=bit(WGM12) | bit(WGM13) | bit(CS12) | bit(CS10); //1024 prescaler
  ICR1=259; //16666 / 64 uS=260 (less one)
  OCR1A=0; //64 / 64 uS=1 (less one)
  TIFR1=bit(TOV1); //clear overflow flag
  TIMSK1=bit(TOIE1); //interrupt on overflow on TIMER1
  #endif
  //TIMER2 - horizontal sync pulses
  pinMode(HSYNCPIN, OUTPUT);
  TCCR2A=bit(WGM20) | bit(WGM21) | bit(COM2B1); //pin3=COM2B1
  TCCR2B=bit(WGM22) | bit(CS21); //8 prescaler
  OCR2A=63; //32 / 0.5 uS=64 (less one)
  OCR2B=7; //4 / 0.5 uS=8 (less one)
  TIFR2=bit(TOV2); //clear overflow flag
  TIMSK2=bit(TOIE2); //interrupt on overflow on TIMER2
  //pins for outputting the colour information
  pinMode(COLORPIN0, OUTPUT);
  pinMode(COLORPIN1, OUTPUT);
  sei(); //SEI włącza przerwania
}

void VGAX::end() {
  //disable TIMER0
  TCCR0A=0;
  TCCR0B=0;
  //disable TIMER1
  TCCR1A=0;
  TCCR1B=0;
  //disable TIMER2
  TCCR2A=0;
  TCCR2B=0;
}

void VGAX::clear(byte color) { //pokrywa cały ekran podanym kolorem
  register byte c=color;
  c&=3;
  register byte c0=(c*4) | c;
  c0|=c0*16;
  unsigned cnt=VGAX_BSIZE;
  byte *o=(byte*)vgaxfb;
  while (cnt--)
    *o++=c0; //iteracja po pozycjach w tablicy pikseli
}

void VGAX::putpixel(byte x, byte y, byte color){
    byte *p=vgaxfb + y*VGAX_BWIDTH + (x>>2); //referencja do informacji o pikselu o podanej pozycji
    byte bitpos=6-(x & 3)*2;
    *p=(*p & ~(3 <<bitpos)) | color <<bitpos; //przypisanie nowego info o pikselu.
}

void VGAX::fillrect(byte x, byte y, byte width, byte height, byte color) {
  byte rh=height;
  while (rh--) {
    byte rw=width, rx=x;
    while (rw--) {
      if (rx<VGAX_WIDTH && y<VGAX_HEIGHT)
        putpixel(rx, y, color);
      rx++;
    }
    y++;
  }
}

void VGAX::tone(unsigned int frequency) {
  afreq=1000000 / frequency / 2 / 32;
  afreq0=afreq;
}

void VGAX::noTone() { 
  afreq0=0; 
}

void VGAX::delay(int msec) {
  while (msec--) {
    unsigned cnt=16000/32; //TODO: use a more precise way to calculate cnt
    while (cnt--)
      asm volatile("nop\nnop\nnop\nnop\n");
  }
}
