//draw.cpp written by KAN 7/17

#include "draw.h"


uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

uint16_t strand_length_array[] = {
  0, //NULL
  STRAND_1_LENGTH,  //Backlight Left
  STRAND_2_LENGTH,  //Backlight Right
  STRAND_3_LENGTH,  //Bridge and Civic Center
  STRAND_4_LENGTH,   //FERRY, TRANSAT, PYRAMID, COIT_W
  STRAND_5_LENGTH    //Brewcade Top & Bottom, Sutro
};

CRGB strand[NUM_STRANDS + 1][STRAND_MAX_LENGTH]; //Add one to allow true indexing and zero selector.

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5



void initLEDs() {
  FastLED.addLeds<WS2811,2, GRB>(strand[1], STRAND_1_LENGTH).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2811,14,GRB>(strand[2], STRAND_2_LENGTH).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2811,7, GRB>(strand[3], STRAND_3_LENGTH).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2811,8, GRB>(strand[4], STRAND_4_LENGTH).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2811,6, GRB>(strand[5], STRAND_5_LENGTH).setCorrection(TypicalLEDStrip);
  // FastLED.addLeds<WS2811,20,GRB>(strand[6], STRAND_3_LENGTH).setCorrection(TypicalLEDStrip);
  // FastLED.addLeds<WS2811,21,GRB>(strand[7], STRAND_4_LENGTH).setCorrection(TypicalLEDStrip);
  // FastLED.addLeds<WS2811,5, GRB>(strand[8], STRAND_5_LENGTH).setCorrection(TypicalLEDStrip);
  // FastLED.setBrightness(185);
  FastLED.setBrightness(125);
  fill_solid(strand[1], STRAND_1_LENGTH, CRGB::Green ); //Brewcade + Sutro
  fill_solid(strand[2], STRAND_2_LENGTH, CRGB::Green ); //? Back Right?
  fill_solid(strand[3], STRAND_3_LENGTH, CRGB::Green ); //Transat?
  fill_solid(strand[4], STRAND_4_LENGTH, CRGB::Green ); //Bridge
  fill_solid(strand[5], STRAND_5_LENGTH, CRGB::Green ); //Back Left

  //USE THIS TO CORRECT PYRAMID!!
  correctPyramid();
  // int s = 14;
  // for (int i=s; i <= (s+16); i++) {
  //   uint8_t r = strand[3][i].r;
  //   strand[3][i].r = strand[3][i].g;
  //   strand[3][i].g = r;
  // }
  FastLED.show();

/*
#define CIVIC_W             20          //601 - 620
#define BRIDGE_W            150         //621 - 770
#define FERRY_W             13          //771 - 783
#define TRANSAT_W           16          //784 - 798
#define PYRAMID_W           4           //799 - 802
#define COIT_W              6           //803 - 808
#define BREWCADE_BOT_W      33          //809 - 841
#define BREWCADE_TOP_W      22          //842 - 863
#define SUTRO_W             3           //864 - 866


*/


  // fill_solid(strand[6], STRAND_1_LENGTH, CRGB::Grey);
  // fill_solid(strand[7], STRAND_1_LENGTH, CRGB::Grey);
  // fill_solid(strand[8], STRAND_1_LENGTH, CRGB::Grey);
}


void correctPyramid() {
  int s = 14;
  for (int i=s; i <= (s+16); i++) {
    uint8_t r = strand[3][i].r;
    strand[3][i].r = strand[3][i].g;
    strand[3][i].g = r;
  }
}

void fill_alternating(CRGB* leds, uint16_t num_leds, const CRGB& c1, const CRGB& c2, uint8_t offset) {
  CRGB currentColor;
  for (int i = 0; i < num_leds; i++) {
      if (i % offset == 0) { //Toggle Color
          if (currentColor == c1) {
              currentColor = c2;
          }
          else {
              currentColor = c1;
          }
      }
      leds[i] = currentColor;
  }
}



void gPattGreen() { // Design 0
  fill_solid(strand[1], STRAND_1_LENGTH, CRGB::Green ); //Brewcade + Sutro
  fill_solid(strand[2], STRAND_2_LENGTH, CRGB::Green ); //? Back Right?
  fill_solid(strand[3], STRAND_3_LENGTH, CRGB::Green ); //Transat?
  fill_solid(strand[4], STRAND_4_LENGTH, CRGB::Green ); //Bridge
  fill_solid(strand[5], STRAND_5_LENGTH, CRGB::Green ); //Back Left
}

void gPattPurpleBlue() { // Design 1
  fill_solid(strand[1], STRAND_1_LENGTH, CRGB::Blue ); //Brewcade + Sutro
  fill_solid(strand[2], STRAND_2_LENGTH, CRGB::DarkViolet ); //? Back Right?
  fill_solid(strand[3], STRAND_3_LENGTH, CRGB::Blue ); //Transat?
  fill_solid(strand[4], STRAND_4_LENGTH, CRGB::Blue ); //Bridge
  fill_solid(strand[5], STRAND_5_LENGTH, CRGB::DarkViolet ); //Back Left
}

void gPattGreenPurple() { // Design 2
  fill_solid(strand[1], STRAND_1_LENGTH, CRGB::Green ); //Brewcade + Sutro
  fill_solid(strand[2], STRAND_2_LENGTH, CRGB::Green ); //? Back Right?
  fill_solid(strand[3], STRAND_3_LENGTH, CRGB::Purple ); //Transat?
  fill_solid(strand[4], STRAND_4_LENGTH, CRGB::Purple ); //Bridge
  fill_solid(strand[5], STRAND_5_LENGTH, CRGB::Green ); //Back Left
}

void gPattBlueGreen() { // Design 3
  fill_solid(strand[1], STRAND_1_LENGTH, CRGB::Green ); //Brewcade + Sutro
  fill_solid(strand[2], STRAND_2_LENGTH, CRGB::Blue ); //? Back Right?
  fill_solid(strand[3], STRAND_3_LENGTH, CRGB::Green ); //Transat?
  fill_solid(strand[4], STRAND_4_LENGTH, CRGB::Green ); //Bridge
  fill_solid(strand[5], STRAND_5_LENGTH, CRGB::Blue ); //Back Left
}

void gPattRedYellow() { // Design 4
  fill_solid(strand[1], STRAND_1_LENGTH, CRGB::Red ); //Brewcade + Sutro
  fill_solid(strand[2], STRAND_2_LENGTH, CRGB::Yellow ); //? Back Right?
  fill_solid(strand[3], STRAND_3_LENGTH, CRGB::Yellow ); //Transat?
  fill_solid(strand[4], STRAND_4_LENGTH, CRGB::Red ); //Bridge
  fill_solid(strand[5], STRAND_5_LENGTH, CRGB::Yellow ); //Back Left
}

void gPattSlowRainbow() { // Design 5
  fill_solid(strand[1], STRAND_1_LENGTH, CHSV(gHue, 255, 255) ); //Brewcade + Sutro
  fill_solid(strand[2], STRAND_2_LENGTH, CHSV(gHue, 255, 255) ); //? Back Right?
  fill_solid(strand[3], STRAND_3_LENGTH, CHSV(gHue, 255, 255) ); //Transat?
  fill_solid(strand[4], STRAND_4_LENGTH, CHSV(gHue, 255, 255) ); //Bridge
  fill_solid(strand[5], STRAND_5_LENGTH, CHSV(gHue, 255, 255) ); //Back Left
}



void gPattPride() {  // Design 6
  fill_rainbow(strand[1], STRAND_1_LENGTH, gHue, 7 ); //Brewcade + Sutro
  fill_rainbow(strand[2], STRAND_2_LENGTH, gHue, 7 ); //? Back Right?
  fill_rainbow(strand[3], STRAND_3_LENGTH, gHue, 7 ); //Transat?
  fill_rainbow(strand[4], STRAND_4_LENGTH, gHue, 7 ); //Bridge
  fill_rainbow(strand[5], STRAND_5_LENGTH, gHue, 7 ); //Back Left
  addGlitter(80);
}

void gPattPatriotic() {  // Design 7
  gPattGreen();
}

void gPattStPatty() {  // Design 8
  gPattGreen();
}

void gPattHalloween() {  // Design 9
  fill_solid(strand[1], STRAND_1_LENGTH, CRGB::Green ); //Brewcade + Sutro
  fill_solid(strand[2], STRAND_2_LENGTH, CRGB::Orange ); //? Back Right?
  fill_solid(strand[3], STRAND_3_LENGTH, CRGB::Orange ); //Transat?
  fill_alternating(strand[4], STRAND_4_LENGTH, CRGB::Orange, CRGB::Purple, 5); //Bridge
  fill_solid(strand[5], STRAND_5_LENGTH, CRGB::Orange ); //Back Left
}

void gPattChristmas() {  // Design 10
  fill_solid(strand[1], STRAND_1_LENGTH, CRGB::Green ); //Brewcade + Sutro
  fill_solid(strand[2], STRAND_2_LENGTH, CRGB::Green ); //? Back Right?
  fill_solid(strand[3], STRAND_3_LENGTH, CRGB::Green ); //Transat?
  fill_alternating(strand[4], STRAND_4_LENGTH, CRGB::Green, CRGB::Red, 5); //Bridge
  fill_solid(strand[5], STRAND_5_LENGTH, CRGB::Green ); //Back Left
}

void gPattSharks() {  // Design 11
  fill_solid(strand[1], STRAND_1_LENGTH, CRGB::Green ); //Brewcade + Sutro
  fill_alternating(strand[2], STRAND_2_LENGTH, CRGB::Silver, CRGB::Teal, 15); //? Back Right?
  fill_alternating(strand[3], STRAND_3_LENGTH, CRGB::Silver, CRGB::Teal, 3); //Transat?
  fill_alternating(strand[4], STRAND_4_LENGTH, CRGB::Silver, CRGB::Teal, 5); //Bridge
  fill_alternating(strand[5], STRAND_5_LENGTH, CRGB::Silver, CRGB::Teal, 15); //Back Left
}

void gPattWarriors() {  // Design 12
  fill_solid(strand[1], STRAND_1_LENGTH, CRGB::Green ); //Brewcade + Sutro
  fill_alternating(strand[2], STRAND_2_LENGTH, CRGB::Yellow, CRGB::DarkBlue, 15); //? Back Right?
  fill_alternating(strand[3], STRAND_3_LENGTH, CRGB::Yellow, CRGB::DarkBlue, 3); //Transat?
  fill_alternating(strand[4], STRAND_4_LENGTH, CRGB::Yellow, CRGB::DarkBlue, 5); //Bridge
  fill_alternating(strand[5], STRAND_5_LENGTH, CRGB::Yellow, CRGB::DarkBlue, 15); //Back Left
}

void gPattGiants(){  // Design 13
  fill_solid(strand[1], STRAND_1_LENGTH, CRGB::Green ); //Brewcade + Sutro
  fill_alternating(strand[2], STRAND_2_LENGTH, CRGB::Orange, CRGB::Black, 15); //? Back Right?
  fill_alternating(strand[3], STRAND_3_LENGTH, CRGB::Orange, CRGB::Black, 3); //Transat?
  fill_alternating(strand[4], STRAND_4_LENGTH, CRGB::Orange, CRGB::Black, 5); //Bridge
  fill_alternating(strand[5], STRAND_5_LENGTH, CRGB::Orange, CRGB::Black, 15); //Back Left
}


void rotateLEDs(CRGB* leds, uint8_t num_LEDs, DIRECTION_TYPE dir) {
  if (dir == DIR_LEFT) {
    leds[num_LEDs-1] = leds[0]; //Roll the first LED over;
    for (int i=0; (i < (num_LEDs -1)); i++) {
      leds[i] = leds[i+1];
    }
  }
  else if (dir == DIR_RIGHT) {
    // leds[0] = leds[num_LEDs-1]; //Roll the first LED over;
    // for (int i=0; (i < (num_LEDs -1)); i++) {
    //   leds[i+1] = leds[i];
    // }
  }

}


void addGlitter( fract8 chanceOfGlitter ) {
  for(int s=1; s < NUM_STRANDS + 1; s++) {
    if( random8() < chanceOfGlitter) {
      strand[s][ random16(strand_length_array[s]) ] += CRGB::White;
    }
  }
}
