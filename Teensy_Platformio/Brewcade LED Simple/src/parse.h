#include <Arduino.h>
#include "draw.h"

#ifndef PARSE_H
#define PARSE_H

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
#define numPatterns 14

typedef enum {
  COM_NULL = 0,

  COM_POWER = 'P',

  COM_PATTERN = 'D',

  COM_BRIGHTNESS = 'B',

  COM_QUERY = '?',

  COM_VERSION = 'V',

} COMMAND_LIST;



extern String inputString;         // a string to hold incoming data
extern uint8_t parameter;
extern bool stringComplete;  // whether the string is complete

extern COMMAND_LIST command;

void parseInput();

#endif
