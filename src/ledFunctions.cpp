#include <Arduino.h>

bool toggleLED(int ledPin){
  int ledState = digitalRead(ledPin);
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