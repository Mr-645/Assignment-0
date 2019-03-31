//PRE-COMPILER DIRECTIVES
#include <Arduino.h>
#include "ledFunctions.h"


//PIN DECLARATION
#define potIN A0  //The pin number of the potentiometer
#define ledPin LED_BUILTIN  //The pin number of the LED
#define interruptPin A1 //The push button pin


//VARIABLE DECLARATION
uint8_t ledState = LOW; //"ledState" is used to store the LED's state
uint32_t interval = 100;  //The interval at which to blink (microseconds)
uint16_t potVal = 0; //The potentiometer set value
float_t dispFreq = 0; //The frequency value to display
bool dispVal = false; //Boolean to decide if values should be displayed or not


void setup() {
  pinMode(ledPin, OUTPUT);  //Sets the digital pin as output
  pinMode(interruptPin, INPUT_PULLUP); //Assigns a pull up resistor to the push button
  Serial.begin(9600); //Initialises serial comms at a baud rate of 9600
  analogReadResolution(12); //Sets the ADC analogue read resolution to 12 bit
  
  //Run the dispValFunc function when the pin is high
  attachInterrupt(digitalPinToInterrupt(interruptPin), dispValFunc, HIGH);
}


void loop() {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  uint32_t currentMicros = micros();
  static uint32_t previousMicros = 0; //This will store the last time the LED was updated

  potVal = analogRead(potIN); //Assigns the potentiometer position to a variable
  interval = potValToTime(potVal); //Performs function to interpolate Pot position to interval time
  dispFreq = 1 / (interval / (10^6)); //It's 10^6 because of microseconds

  if (currentMicros - previousMicros >= interval) {
    previousMicros = currentMicros; //Saves the last time you blinked the LED
    toggleLED(ledPin); //Perform function of toggling LED

    if (dispVal == true) {
      //If dispVal is true, print frequency value to serial monitor
      Serial.print(dispFreq);
      Serial.println(" Hz"); 
      Serial.flush();
    }
    else
    {
      /* code */
    }
    
  }
}

void dispValFunc(){
  dispVal = true; //Set the boolen dispVal to true
}