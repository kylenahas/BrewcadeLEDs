#include "parse.h"

#define SCB_AIRCR (*(volatile uint32_t *)0xE000ED0C) // Application Interrupt and Reset Control location

void _softRestart()
{
  Serial.end();  //clears the serial monitor  if used
  SCB_AIRCR = 0x05FA0004;  //write value for restart
}

String inputString = "";
uint8_t parameter = 0;
bool stringComplete = false;
bool successfulCommand = false;
COMMAND_LIST command = COM_NULL;
// char cCommand;
uint8_t currentBrightness = 150;
uint8_t numberOfUnsuccessfulCommands = 0;

// /*
void parseInput() {
  // if (Serial.available()) {
    // digitalWrite(LED_BUILTIN, HIGH);
    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read();
      // add it to the inputString:
      inputString += inChar;
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
      if (inChar == '\n') {
        stringComplete = true;
        digitalWrite(LED_BUILTIN, HIGH);
      }
    }
  // }

  // print the string when a newline arrives:
  if (stringComplete) {
    //Process the data
    // Serial.println(inputString);
    command = (COMMAND_LIST)inputString.charAt(0);
    // command = (COMMAND_LIST)cCommand;
    inputString.remove(0, 1);
    parameter = inputString.toInt();
    //
    // Serial.print("Command: ");
    // Serial.println((char)command);
    successfulCommand = true;

    switch (command) {
      case COM_POWER: {
        if (parameter == 0) {
          FastLED.setBrightness(0);
          Serial.println("Power Off");
        }
        else if(parameter == 1) {
          FastLED.setBrightness(currentBrightness);
          Serial.print("Brightness set to: ");
          Serial.println(currentBrightness);
        }
        break;
      }

      case COM_PATTERN: {
        if (parameter < numPatterns) {
          gCurrentPatternNumber = parameter;
          Serial.print("Pattern set to: ");
          Serial.println(gCurrentPatternNumber);
        }
        break;
      }

      case COM_BRIGHTNESS: {
        currentBrightness = parameter;
        FastLED.setBrightness(currentBrightness);
        Serial.print("Brightness set to: ");
        Serial.println(currentBrightness);
        break;
      }

      case COM_QUERY: {
        Serial.println("Teensy LED Controller");
        break;
      }

      case COM_VERSION: {
        Serial.println("SW=1.0.2,HW=Teensy3.2");
        break;
      }

      default: {
        Serial.print("Invalid Command:");
        Serial.println(command);
        successfulCommand = false;
        numberOfUnsuccessfulCommands++;

        if (numberOfUnsuccessfulCommands > 10) {
          Serial.println("Too many invalid commands. Rebooting!");
          _softRestart();
        }
        //Do nothing
        break;
      }

    }


    inputString = "";
    stringComplete = false;
    digitalWrite(LED_BUILTIN, LOW);

    if (successfulCommand) {
      numberOfUnsuccessfulCommands = 0;
    }
  }
}

// */


// void serialEvent() {
//   while (Serial.available()) {
//     // get the new byte:
//     char inChar = (char)Serial.read();
//     // add it to the inputString:
//     inputString += inChar;
//     // if the incoming character is a newline, set a flag
//     // so the main loop can do something about it:
//     if (inChar == '\n') {
//       stringComplete = true;
//       digitalWrite(LED_BUILTIN, HIGH);
//     }
//   }
// }
