#include <Arduino.h>
#include "draw.h"
#include "parse.h"

FASTLED_USING_NAMESPACE

#define FRAMES_PER_SECOND  120
#define NUM_LEDS    15
CRGB leds[NUM_LEDS];

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

bool toggle;

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {
  gPattGreen,
  gPattPurpleBlue,
  gPattGreenPurple,
  gPattBlueGreen,
  gPattRedYellow,
  gPattSlowRainbow,

  gPattPride,
  gPattPatriotic,
  gPattStPatty,
  gPattHalloween,
  gPattChristmas,

  gPattSharks,
  gPattWarriors,
  gPattGiants,

};

void setup() {
    // put your setup code here, to run once:

    Serial.begin(115200); // USB is always 12 Mbit/sec
    initLEDs();
    pinMode(LED_BUILTIN, OUTPUT);
    // reserve 200 bytes for the inputString:
    inputString.reserve(200);
}

void loop() {
    
    parseInput();
    // Call the current pattern function once, updating the 'leds' array
    gPatterns[gCurrentPatternNumber]();

    // correct the inverted leds before sending out
    correctPyramid();
    // send the 'leds' array out to the actual LED strip
    FastLED.show();
    // insert a delay to keep the framerate modest
    FastLED.delay(1000/FRAMES_PER_SECOND);


    // do some periodic updates
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow

    // EVERY_N_SECONDS(1) {
    //   toggle = !toggle;
    //   digitalWrite(LED_BUILTIN, toggle);
    //
    // }
}
