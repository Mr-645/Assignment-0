//PRE-COMPILER DIRECTIVES
#include <Arduino.h>
#include <PWM.h>


//PIN DECLARATION
#define potInVal A0  //The pin number of the potentiometer
#define signal_out_pin 9  //The pin number of the LED
#define ledPin 13 //LED builtin pin
#define interruptPin 2 //The push button pin


//VARIABLE DECLARATION
uint8_t ledState = LOW; //"ledState" is used to store the LED's state
unsigned long debounceDelay = 100;  //Debounce time - Switch ignore time
unsigned long lastDebounceTime = 0; //This will store the last time the LED was updated
bool allowDispVal = true; //Boolean to decide to allow display code execution
int32_t frequency = 1000; //PWM frequency
double outPWM = 50*655; //PWM duty cycle set to 50%


//Function to give clearance for serial output
void dispValFunc(){
  if (allowDispVal == true) {
    //If allowDispVal is true, print frequency value to serial monitor
    Serial.print(frequency);
    Serial.println(" Hz");
    Serial.flush();
    lastDebounceTime = millis(); //Reset last debounce time
  }
}


void setup() {
  pinMode(signal_out_pin, OUTPUT);  //Sets the digital pin as output
  pinMode(ledPin, OUTPUT); //Sets the builtin led pin as an output
  pinMode(interruptPin, INPUT_PULLUP); //Assigns a pull up resistor to the push button
  Serial.begin(9600); //Initialises serial comms at a baud rate of 9600

  InitTimersSafe(); //Initialise PWM function
  bool success = SetPinFrequencySafe(signal_out_pin, frequency); //Set PWM frequency

  //Run the dispValFunc function when the pin is goes low
  attachInterrupt(digitalPinToInterrupt(interruptPin), dispValFunc, FALLING);
}


void loop() {
  //Assigns the potentiometer position to a variable
  frequency = map(analogRead(potInVal), 0, 903, 10, 5000);

  SetPinFrequencySafe(signal_out_pin, frequency); //Live set/edit PWM frequency
  pwmWriteHR(signal_out_pin, outPWM); //Set PWM duty cycle

  if (millis() - lastDebounceTime >= debounceDelay){
    allowDispVal = true;
    digitalWrite(ledPin, LOW);
  }
  else
  {
    allowDispVal = false;
    digitalWrite(ledPin, HIGH);
  }
}