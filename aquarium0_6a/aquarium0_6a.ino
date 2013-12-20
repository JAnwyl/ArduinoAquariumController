/*
//**************** ArduinoAquariumController ****************
//Version :   0.6 Alpha
//AUTHOR :    Jared Anwyl jaredanwyl@gmail.com
//LICENSE :   GPL
//DONE :      Nothing
//TODO :      Phase #1
//**********************************************************
I want to make this version stripped down
except for comments of future features
This is Psuedo Code/realcode for my aquarium controller

I stole the design of Roger Reeds autofeeder. Thanks Roger!
Not only do you have a incredible controller but an incredible tank

This code is public domain

  Table of contents:
  Libraries                                 - [#LIBRARIES]
  Global Variables                          - [#VAR]
  Pins                                      - [#PIN]
 
  Setup Function                            - [#SETUP]
  
  Start Of Main Loop                        - [#LOOP]
  
  Methods                                   - [#METHODS]
 */

////////////////////////////////////Libraries///////////////////////////////////////
///////////////////////////////////#LIBRARIES///////////////////////////////////////
#include <dht.h> //dht
#include <Wire.h> //LCD
#include <LCD.h> //LCD
#include <LiquidCrystal_I2C.h> //LCD
#include <OneWire.h> //DS18B20
#include <DallasTemperature.h> //DS18B20

////////////////////////////////Global Variables////////////////////////////////////
/////////////////////////////////////#VAR///////////////////////////////////////////
float displayDTTemp;
float displaySumpTemp;
float displayHoodTemp;
float displayAmbientTemp;
float currentTime;
boolean waveMaker;
//boolean feeding;

/////////////////////////////////////Define Pins////////////////////////////////////
///////////////////////////////////////#PIN/////////////////////////////////////////
// constants won't change. They're used here to 
// set pin numbers:
//digital 0 and 1 are reserved for tx and rx on mega and uno
//On mega pins 14-19 are rx and tx 20 & 21 are sda & scl 22-53 are plain digital 2-13 are pwm
const int uvPumpRelay = 2; //Relay
const int uvLightRelay = 3; //Relay
const int returnPump = 4; //Relay
const int proteinSkimmer = 5; //Relay
const int displayPumpLeft = 6; //Relay
const int displayPumpRight = 7; //Relay
const int heater = 8; //Relay
//const int relay_1 = 9;
const int rtcIn = 10;
const int rtcOut = 11;
const int alarmButton = 12;
const int alarm = 13;
const int lm = 22;
const int sumpHi = 23;
const int sumpLow = 24;
const int skimmerHi= 25;
#define dht_dpin A0
//const int feeder = 14;
//const int blueIn = ;
//const int blueOut = ;
//const int IR = ;

///////////////////////////////////////Setup////////////////////////////////////////
/////////////////////////////////////#SETUP/////////////////////////////////////////
void setup() {
  Serial.begin(9600); 
   pinMode(uvPumpRelay, OUTPUT);//Relay
   pinMode(uvLightRelay, OUTPUT);//Relay
   pinMode(returnPump, OUTPUT);//Relay
   pinMode(proteinSkimmer, OUTPUT);//Relay
   pinMode(displayPumpLeft, OUTPUT);//Relay
   pinMode(displayPumpRight, OUTPUT);//Relay
   pinMode(heater, OUTPUT);//Relay
   //pinMode(9, OUTPUT);//Relay
   pinMode(rtcIn, INPUT);//RTC
   pinMode(rtcOut, OUTPUT);//RTC
   //pinMode(lcd, OUTPUT);//LCD
   pinMode(alarmButton, INPUT);//Alarm Button
   pinMode(alarm, OUTPUT);//Alarm Piezo
   pinMode(lm, INPUT);
   pinMode(sumpHi, INPUT);
   pinMode(sumpLow, INPUT);
   pinMode(skimmerHi, INPUT);
   //pinMode(feeder, OUTPUT);//Feeding Stepper Motor
   //pinMode(blueIn, INPUT);//BlueTooth
   //pinMode(blueOut, OUTPUT);//BlueTooth
   //pinMode(IR, INPUT);//IR
}

/////////////////////////////////////Loop///////////////////////////////////////////
/////////////////////////////////////#LOOP//////////////////////////////////////////

void loop() {
/*  
    switch () {
      case 'a':    
        displayPumpsOn();//W/O Wavemaker
        break;
      case 'b':    
        waves();//W/Wavemaker
        break;
      case 'c':    
        displayPumpsOff();//Water Change
        returnPumpOff();
        break;
      case 'd':    
        sumpOff();//Sump Maintenance
        break;
      case 'e':    
        displayPumpsOff();//Display Maintenance
        break;
      default:
        displayPumpsOn();//W/O Wavemaker
        break;
      }
*/      
}

/////////////////////////////////////Methods////////////////////////////////////////
/////////////////////////////////////#METHODS///////////////////////////////////////
void temp(){
  //Controls Heater
  //This isn't right
  //79 is Optimal
  if(displayDTTemp <= 77.00){
  	heaterOn();
  }else if(displayDTTemp >=  82.00){
  	heaterOff();
  }
}

void lights(){
  //Display Lighting System
  //On/Off & Dim (Actinic, White, other LED control/color, 2+ Relays)
  //setup dimming if get LEDs
  if(currentTime == 11.00){
  	actinicOn();
  }else if(currentTime == 12.00){
  	whiteOn();
  }else if(currentTime == 22.00){
  	whiteOff();
  }else if(currentTime == 23.00){
  	actinicOff();
  }
}

void moonlights(){
  //Moonlight System (1 Relay)
  //Socket for Moonlights
  if(currentTime == 22.59){
  	moonlightOn();
  }else if(currentTime == 11.01){
  	moonlightOff();
  }
}

void fan(){
  //Fan System
  //Always on During Display Lighting System
  //Adjust Voltage depending on Display lighting temp
  //30% - 100%
  //Fans to blow on sump if water temp rises to threshold
}

void waves(){
	while(waveMaker == true){//Check format
		displayPumpLeftOn();
		displayPumpRightOff();
		delay(20000);
		displayPumpLeftOff();
		displayPumpRightOn();
		delay(20000);
	}
	Serial.print("Waves");
}

void allOn(){
	displayPumpsOn();
	sumpOn();
	returnPumpOn();
	Serial.print("All on minus lights");
}

void allOff(){
	displayPumpsOff();
	sumpOff();
	returnPumpOff();
	Serial.print("All off minus lights");
}
		
void displayPumpsOn(){
	displayPumpLeftOn();
	displayPumpRightOn();
	Serial.print("Display pumps on");
}

void displayPumpsOff(){
	displayPumpLeftOff();
	displayPumpRightOff();
	Serial.print("Display pumps off");
}

void displayPumpLeftOn(){
	digitalWrite(displayPumpLeft, HIGH);
	Serial.print("Display pump left on");
}

void displayPumpRightOn(){
	digitalWrite(displayPumpRight, HIGH);
	Serial.print("Display pump right on");
}

void displayPumpLeftOff(){
	digitalWrite(displayPumpLeft, LOW);
	Serial.print("Display pump left off");
}

void displayPumpRightOff(){
	digitalWrite(displayPumpRight, LOW);
	Serial.print("Display pump right off");
}

void heaterOn(){
	digitalWrite(heater, HIGH);
	Serial.print("Heater on");
}

void heaterOff(){
	digitalWrite(heater, LOW);
	Serial.print("Heater off");
}

void whiteOn(){
	//digitalWrite(, HIGH;)
	Serial.print("White on");
}

void whiteOff(){
	//digitalWrite(, LOW;)
	Serial.print("White off");
}

void actinicOn(){
	//digitalWrite(, HIGH;)
	Serial.print("Actinic on");
}

void actinicOff(){
	//digitalWrite(, LOW;)
	Serial.print("Actinic off");
}

void moonlightOn(){
	//digitalWrite(, HIGH;)
	Serial.print("Moonlight on");
}

void moonlightOff(){
	//digitalWrite(, LOW;)
	Serial.print("Moonlight off");
}

void returnPumpOn(){
	digitalWrite(returnPump, HIGH);
	Serial.print("Return pump on");
}

void returnPumpOff(){
	digitalWrite(returnPump, LOW);
	Serial.print("Return pump off");
}

void protienSkimmerOn(){
	digitalWrite(proteinSkimmer, HIGH);
	Serial.print("Protien skimmer on");
}

void protienSkimmerOff(){
	digitalWrite(proteinSkimmer, LOW);
	Serial.print("Protien skimmer off");
}

void ultraVioletOn(){
	digitalWrite(uvPumpRelay, HIGH);//Pump
	digitalWrite(uvLightRelay, HIGH);//Light
	Serial.print("Ultra violet on");
}

void ultraVioletOff(){
	digitalWrite(uvPumpRelay, LOW);//Pump
	digitalWrite(uvLightRelay, LOW);//Light
	Serial.print("Ultra violet off");
}

void sumpOn(){
	ultraVioletOn();
	protienSkimmerOn();
	heaterOn();
	Serial.print("Sump on minus return pump");
}

void sumpOff(){
	ultraVioletOff();
	protienSkimmerOff();
	heaterOff();
	Serial.print("Sump off minus return pump");
}

void alert(){//alert
        digitalWrite(alarm, HIGH);//Speaker
        delay(1000);
        digitalWrite(alarm, LOW);//Speaker
	Serial.print("Alert");
}

/*
void alertButton(){
  // The circuit:
  // * pushbutton attached from pin 2 to +5V
  // * 10K resistor attached from pin 2 to ground
  // Variables will change:
  int lastButtonState = LOW;   // the previous reading from the input pin

  // the following variables are long's because the time, measured in miliseconds,
  // will quickly become a bigger number than can be stored in an int.
  long lastDebounceTime = 0;  // the last time the output pin was toggled
  long debounceDelay = 50;    // the debounce time; increase if the output flickers
  
  void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(alarmButton);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        digitalWrite(alarm, LOW;)//Speaker
      }
    }
  }
  
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
  Serial.print("Quiet alert speaker");
}
*/
