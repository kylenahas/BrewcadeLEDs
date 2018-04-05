//draw.h written by KAN 7/17
#include <Arduino.h>
#include <FastLED.h>


#ifndef DRAW_H
#define DRAW_H


#define MTU 64

#define NUM_STRANDS 5
#define STRAND_MAX_LENGTH 600

#define STRAND_1_LENGTH 58   //Brewcade Top & Bottom, Sutro
#define STRAND_2_LENGTH 300   //Back Right ??
#define STRAND_3_LENGTH 39   //FERRY, TRANSAT, PYRAMID, COIT_W
#define STRAND_4_LENGTH 170    //Bridge and Civic Center
#define STRAND_5_LENGTH 600    //Back Left

// #define STRAND_1_LENGTH STRAND_MAX_LENGTH
// #define STRAND_2_LENGTH STRAND_MAX_LENGTH
// #define STRAND_3_LENGTH STRAND_MAX_LENGTH
// #define STRAND_4_LENGTH STRAND_MAX_LENGTH
// #define STRAND_5_LENGTH STRAND_MAX_LENGTH

extern uint8_t gCurrentPatternNumber; // Index number of which pattern is current
extern uint8_t gHue; // rotating "base color" used by many of the patterns
extern uint8_t currentBrightness; // rotating "base color" used by many of the patterns


typedef unsigned char uint8_t;

typedef enum {

  DIR_NONE,

  DIR_RIGHT,

  DIR_LEFT,
} DIRECTION_TYPE;


void initLEDs();
void correctPyramid();
uint8_t draw(uint8_t *payload, uint8_t length);
void fill_alternating(CRGB* leds, uint16_t num_leds, const CRGB& c1, const CRGB& c2, uint8_t offset);
void clearBuff();
void animate();

void rotateLEDs(CRGB* leds, uint8_t num_LEDs, DIRECTION_TYPE dir);
void addGlitter( fract8 chanceOfGlitter);




void gPattGreen();
void gPattPurpleBlue();
void gPattGreenPurple();
void gPattBlueGreen();
void gPattRedYellow();
void gPattSlowRainbow();

void gPattPride();
void gPattPatriotic();
void gPattStPatty();
void gPattHalloween();
void gPattChristmas();

void gPattSharks();
void gPattWarriors();
void gPattGiants();

#endif
