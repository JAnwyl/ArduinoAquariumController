/*
//**************** ArduinoAquariumController ****************
//Version :   0.7 Alpha
//AUTHOR :    Jared Anwyl jaredanwyl@gmail.com
//LICENSE :   GPL
//TODO :      Read Software & Hardware
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
#include <Wire.h> //LCD & Menu
#include <LiquidCrystal_I2C.h> //LCD & Menu
#include <LCD.h> //Menu
#include <OneWire.h> //DS18B20
#include <DallasTemperature.h> //DS18B20
#include <DS1302.h> //RTC
#include <buttons.h> //Menu
#include <EEPROM.h> //Menu
#include <MENWIZ.h> //Menu

////////////////////////////////Global Variables////////////////////////////////////
/////////////////////////////////////#VAR///////////////////////////////////////////
double dTTempC, dTTempF;
double sumpTempC, sumpTempF;
double hoodTempC, hoodTempF;
double ambientTempC, ambientTempF;
double currentTime;
boolean waveMaker;
boolean feeding;
String AmPm;

int      tp=0;
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
//lcd uses sda & scl or 20 &21
const int sumpHi = 23;
const int sumpLow = 24;
const int skimmerHi= 25;
// DEFINE ARDUINO PINS FOR THE NAVIGATION BUTTONS
#define UP_BUTTON_PIN       26
#define DOWN_BUTTON_PIN     27
#define CONFIRM_BUTTON_PIN  28
#define ESCAPE_BUTTON_PIN   29
//const int feeder = ;
//const int blueIn = ;
//const int blueOut = ;
//const int IR = ;

//Analog Pins
#define dht_dpin A0
#define ONE_WIRE_BUS 1
const int lm35 = 3;

dht DHT;
menwiz menu;
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
  rtc.halt(false);              // Set the clock to run-mode
  sensors.begin();              // DS18B20
  _menu *r,*s1,*s2;             //Menu
  menu.begin(&lcd,20,4);        // inizialize the menu object (20 colums x 4 rows)
  
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
   
  //create the menu tree
  r=menu.addMenu(MW_ROOT,NULL,F("MAIN MENU"));
    s1=menu.addMenu(MW_SUBMENU,r,F("Settings"));
      s2=menu.addMenu(MW_VAR,s1,F("Set RTC"));
        s2->addVar(MW_LIST,&tp);
        s2->addItem(MW_LIST,F("Day of Week"));
        s2->addItem(MW_LIST,F("24 Hour"));
        s2->addItem(MW_LIST,F("Min"));
        s2->addItem(MW_LIST,F("Year"));

    s1=menu.addMenu(MW_VAR,r,F("W/Wavemaker"));
      s1->addVar(MW_ACTION,waves);
      
    s1=menu.addMenu(MW_VAR,r,F("W/O Wavemaker"));
      s1->addVar(MW_ACTION,displayPumpsOn);
      
    s1=menu.addMenu(MW_VAR,r,F("Waterchange"));
      s1->addVar(MW_ACTION,displayPumpsOff);
      
    s1=menu.addMenu(MW_VAR,r,F("Sump Maintenance"));
      s1->addVar(MW_ACTION,sumpOff);
      
    s1=menu.addMenu(MW_VAR,r,F("Display Maintenance"));
      s1->addVar(MW_ACTION,displayPumpsOff);
      
  menu.navButtons(UP_BUTTON_PIN,DOWN_BUTTON_PIN,ESCAPE_BUTTON_PIN,CONFIRM_BUTTON_PIN);

  menu.addUsrScreen(usrScreen,10000);
}

/////////////////////////////////////Loop///////////////////////////////////////////
/////////////////////////////////////#LOOP//////////////////////////////////////////
void loop() {
  DHT.read11(dht_dpin);
  sensors.requestTemperatures();        //DS18B20
  menu.draw();
  ambientTempC = analogRead(dht_dpin);
  ambientTempC = ambientTempC * 0.48828125;
  ambientTempF = (ambientTempC * 9)/ 5 + 32;
  dTTempC = (sensors.getTempCByIndex(0));
  dTTempF = (dTTempC * 9)/ 5 + 32;
  hoodTempC = DHT.temperature;
  hoodTempF = (hoodTempC * 9)/ 5 + 32;
}

/////////////////////////////////////Methods////////////////////////////////////////
/////////////////////////////////////#METHODS///////////////////////////////////////
void usrScreen(){
  static  char buf[7];
  strcpy(menu.sbuf,"Clock:");                   //1st lcd line
  //Serial.print(rtc.getDateStr([[FORMAT_SHORT]FORMAT_MIDDLEENDIAN]));
  //Serial.print(rtc.getDOWStr());
  //Serial.println(rtc.getTimeStr([FORMAT_SHORT]));
  strcat(menu.sbuf,"\nAmbient Temp: ");         //2nd lcd line temp = analogRead(tempPin);
  strcat(menu.sbuf,"\nTank Temp: ");            //3rd lcd line Serial.print(sensors.getTempCByIndex(0));
  strcat(menu.sbuf,"\nHood Temp: ");            //4th lcd line Serial.print(DHT.temperature);
  menu.drawUsrScreen(menu.sbuf);
}

/*
void usrScreen(){
    lcd.begin(20,4);               // initialize the lcd 
    lcd.backlight();
    lcd.home ();
    lcd.setCursor(0, 0);
    lcd.print("Clock:");
    lcd.print(rtc.getTimeStr([FORMAT_SHORT]));
    lcd.setCursor(0, 1);
    lcd.print("Ambient Temp:");
    lcd.print(ambientTempF);
    lcd.print("F");
    lcd.setCursor(0, 2);
    lcd.print("Tank Temp:");
    lcd.print(dTTempF);
    lcd.print("F");
    lcd.setCursor(0, 3);
    lcd.print("Hood Temp:");
    lcd.print(hoodTempF);
    lcd.print("F");
}
*/

void waves(){
  displayPumpLeftOn();
  displayPumpRightOff();
  delay(20000);
  displayPumpLeftOff();
  displayPumpRightOn();
  delay(20000);
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
