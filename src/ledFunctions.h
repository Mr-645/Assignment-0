//Header guard - to prevent a re-copy of variables
#ifndef LEDFUNCTION_H
#define LEDFUNCTION_H

#include <Arduino.h>

//Function prototype
bool toggleLED(uint8_t ledPin);
bool potValToTime(uint16_t potVal);

#endif