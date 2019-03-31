#include <Arduino.h>

bool toggleLED(uint8_t ledPin){
  uint8_t ledState = digitalRead(ledPin);
  // if the LED is off turn it on and vice-versa:
  if (ledState == LOW) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }

  // set the LED with the ledState of the variable:
  digitalWrite(ledPin, ledState);
  return ledState;
}

bool potValToTime(uint16_t potVal){
  //Map Pot position of 0-max to 1000000-200 microseconds
  uint32_t interval = map(potVal, 0, 4095, 1000000, 200);
  return interval;
}