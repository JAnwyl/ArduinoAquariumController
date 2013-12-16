/*
Jared Anwyl
Turns on and off a light emitting diode(LED) connected to digital  
pin 13, when using a float switch attached to pin 2.
This works like 75% of time.
Done

The circuit:
* LED attached from pin 13 to ground 
* Float Switch attached to pin 2 from +5V
* 10K resistor attached to pin 2 from ground

This example code is in the public domain.
*/

// constants won't change. They're used here to 
// set pin numbers:
const int floatPin = 2;     // the number of the Float pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(floatPin, INPUT);     
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(floatPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}
