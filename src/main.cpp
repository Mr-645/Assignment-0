//PRE-COMPILER DIRECTIVES
#include <Arduino.h>
#include <PWM.h>


//PIN DECLARATION
#define potInVal A0  //The pin number of the potentiometer
#define signal_out_pin 9  //The pin number of the LED
#define ledPin 13 //LED builtin pin
#define interruptPin 2 //The push button pin


//VARIABLE DECLARATION
uint8_t ledState = LOW; //"ledState" is used to store the inbuilt LED's state
uint32_t debounceDelay = 100;  //Debounce time interval (button ignore time)
uint32_t lastDebounceTime = 0; //This will store the last time the button was pressed
bool allowDispVal = true; //Boolean to decide to allow display code execution
uint16_t frequency = 1000; //Initialise the PWM frequency
uint64_t outPWM = 50*655; //Initialise (in this case, set) the PWM duty cycle set to 50%


//Function to give clearance for serial output
void dispValFunc(){
  if (allowDispVal == true) {
    //If allowDispVal is true, print the following to the serial monitor
    Serial.print(frequency); //Start the line with the number for the frequency variable
    Serial.println(" Hz"); //End the line with the suffix "Hz" following a whitespace
    Serial.flush(); //Force the send buffer to be cleared
    lastDebounceTime = millis(); //Reset the value of the last button press (or bounce) time
  }
}


void setup() {
  pinMode(signal_out_pin, OUTPUT);  //Sets the digital pin as output
  pinMode(ledPin, OUTPUT); //Sets the builtin led pin as an output
  pinMode(interruptPin, INPUT_PULLUP); //Assigns a pull up resistor to the push button
  Serial.begin(9600); //Initialises serial comms at a baud rate of 9600

  InitTimersSafe(); //Initialise PWM function
  /*bool success = */SetPinFrequencySafe(signal_out_pin, frequency); //Set PWM frequency

  //Run the dispValFunc function when the pin is goes low
  attachInterrupt(digitalPinToInterrupt(interruptPin), dispValFunc, FALLING);
}


void loop() {
  //Assigns the 10-bit potentiometer position to a variable
  frequency = map(analogRead(potInVal), 0, 926, 10, 5000);

  SetPinFrequencySafe(signal_out_pin, frequency); //Live set/edit PWM frequency
  pwmWriteHR(signal_out_pin, outPWM); //Set PWM duty cycle

  //Compare the difference between the last timing and the current time to an interval
  if (millis() - lastDebounceTime >= debounceDelay){
    allowDispVal = true; //Set the serial display boolean to true
    digitalWrite(ledPin, LOW); //Turn the inbuilt led off
  }
  else  {
    allowDispVal = false; //Set the serial display boolean to false
    digitalWrite(ledPin, HIGH); //Turn the inbuilt led on
  }
}