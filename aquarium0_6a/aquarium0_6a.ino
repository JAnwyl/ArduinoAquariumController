/*
//**************** ArduinoAquariumController ****************
//Version :   0.6 Alpha
//AUTHOR :    Jared Anwyl jaredanwyl@gmail.com
//LICENSE :   GPL
//DONE :      Nothing
//TODO :      Phase #1
//**********************************************************
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
#include <LiquidCrystal_I2C.h> //LCD
#include <OneWire.h> //DS18B20
#include <DallasTemperature.h> //DS18B20
#include <DS1302.h> //RTC

////////////////////////////////Global Variables////////////////////////////////////
/////////////////////////////////////#VAR///////////////////////////////////////////
double displayDTTempC, displayDTTempF;
double displaySumpTempC, displaySumpTempF;
double displayHoodTempC, displayHoodTempF;
double displayAmbientTempC, displayAmbientTempF;
double currentTime;
boolean waveMaker;
boolean feeding;
String AmPm;

/////////////////////////////////////Define Pins////////////////////////////////////
///////////////////////////////////////#PIN/////////////////////////////////////////
// constants won't change. They're used here to 
// set pin numbers:
//digital 0 and 1 are reserved for tx and rx on mega and uno
//22-53 are plain digital 2-13 are pwm
const int uvPumpRelay = 2; //Relay
const int uvLightRelay = 3; //Relay
const int returnPump = 4; //Relay
const int proteinSkimmer = 5; //Relay
const int displayPumpLeft = 6; //Relay
const int displayPumpRight = 7; //Relay
const int heater = 8; //Relay
//const int relay_1 = 9;
//10-12 are gonna be rtc
const int alarm = 13;
//On mega pins 14-19 are rx and tx 20 & 21 are sda & scl
//lcd uses sda & scl
const int sumpHi = 23;
const int sumpLow = 24;
const int skimmerHi= 25;
//const int feeder = ;
//const int blueIn = ;
//const int blueOut = ;
//const int IR = ;
const int debounceTime = 20; // number of milliseconds for switch to be stable

//Analog Pins
#define dht_dpin A0
#define ONE_WIRE_BUS 2
const int lm35 = 22;

dht DHT;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

//Addr: 0x3F, 20 chars & 4 lines
LiquidCrystal_I2C	lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE);

DS1302 rtc(10, 11, 12); //10,11,12 Are RTC pins

///////////////////////////////////////Setup////////////////////////////////////////
/////////////////////////////////////#SETUP/////////////////////////////////////////
void setup() {
  // Set the clock to run-mode
  rtc.halt(false);
  lcd.begin(20,4);               // initialize the lcd 
  lcd.backlight();
  lcd.home ();
  lcd.setCursor(0, 0);
  lcd.print("Arduino Aquarium");
  lcd.setCursor(0, 1);
  lcd.print("Controller");
  sensors.begin();               // DS18B20
  
  Serial.begin(9600); 
   pinMode(uvPumpRelay, OUTPUT);//Relay
   pinMode(uvLightRelay, OUTPUT);//Relay
   pinMode(returnPump, OUTPUT);//Relay
   pinMode(proteinSkimmer, OUTPUT);//Relay
   pinMode(displayPumpLeft, OUTPUT);//Relay
   pinMode(displayPumpRight, OUTPUT);//Relay
   pinMode(heater, OUTPUT);//Relay
   //pinMode(9, OUTPUT);//Relay
   pinMode(alarm, OUTPUT);//Alarm Piezo
   pinMode(lm35, INPUT);
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
  DHT.read11(dht_dpin);
  sensors.requestTemperatures();//DS18B20
  
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
  if(displayDTTempF <= 77.00){
  	heaterOn();
  }else if(displayDTTempF >=  82.00){
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
  //Moonlight System
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
}

void allOn(){
	displayPumpsOn();
	sumpOn();
	returnPumpOn();
}

void allOff(){
	displayPumpsOff();
	sumpOff();
	returnPumpOff();
}
		
void displayPumpsOn(){
	displayPumpLeftOn();
	displayPumpRightOn();
}

void displayPumpsOff(){
	displayPumpLeftOff();
	displayPumpRightOff();
}

void displayPumpLeftOn(){
	digitalWrite(displayPumpLeft, HIGH);
}

void displayPumpRightOn(){
	digitalWrite(displayPumpRight, HIGH);
}

void displayPumpLeftOff(){
	digitalWrite(displayPumpLeft, LOW);
}

void displayPumpRightOff(){
	digitalWrite(displayPumpRight, LOW);
}

void heaterOn(){
	digitalWrite(heater, HIGH);
}

void heaterOff(){
	digitalWrite(heater, LOW);
}

void whiteOn(){
	//digitalWrite(, HIGH;)
}

void whiteOff(){
	//digitalWrite(, LOW;)
}

void actinicOn(){
	//digitalWrite(, HIGH;)
}

void actinicOff(){
	//digitalWrite(, LOW;)
}

void moonlightOn(){
	//digitalWrite(, HIGH;)
}

void moonlightOff(){
	//digitalWrite(, LOW;)
}

void returnPumpOn(){
	digitalWrite(returnPump, HIGH);
}

void returnPumpOff(){
	digitalWrite(returnPump, LOW);
}

void protienSkimmerOn(){
	digitalWrite(proteinSkimmer, HIGH);
}

void protienSkimmerOff(){
	digitalWrite(proteinSkimmer, LOW);
}

void ultraVioletOn(){
	digitalWrite(uvPumpRelay, HIGH);//Pump
	digitalWrite(uvLightRelay, HIGH);//Light
}

void ultraVioletOff(){
	digitalWrite(uvPumpRelay, LOW);//Pump
	digitalWrite(uvLightRelay, LOW);//Light
}

void sumpOn(){
	ultraVioletOn();
	protienSkimmerOn();
	heaterOn();
}

void sumpOff(){
	ultraVioletOff();
	protienSkimmerOff();
	heaterOff();
}

void alert(){//alert
        playTone(750, 500);
        delay(750);
}

// duration in mSecs, frequency in hertz
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(alarm,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(alarm, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}

void setRTC(){
  rtc.writeProtect(false);
  //above turns off write protect bit
  
  // The following lines can be commented out to use the values already stored in the DS1302
  rtc.setDOW(THURSDAY);        // Set Day-of-Week to THURSDAY
  rtc.setTime(20, 30, 0);     // Set the time to 8:30:00 (24hr format)
  rtc.setDate(19, 12, 2013);   // Set the date to December 19th, 2013
}

void getRTC(){
  //Convert char to double
  //currentTime = rtc.getTimeStr(2);
  rtc.getTimeStr(2);
}


void getAmPm(){
  char temporaryTime;
  //char temporaryTime = rtc.getTimeStr();
  if (temporaryTime > 12){
    temporaryTime = temporaryTime - 12;
    AmPm = "Pm";
  }else{
    AmPm = "Am";
  }
}

