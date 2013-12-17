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

/////////////////////////////////////////Libraries////////////////////////////////////////////
////////////////////////////////////////#LIBRARIES////////////////////////////////////////////


/////////////////////////////////////Global Variables/////////////////////////////////////////
//////////////////////////////////////////#VAR////////////////////////////////////////////////
float displayDTTemp;
float displaySumpTemp;
float displayHoodTemp;
float displayAmbientTemp;
float currentTime;
boolean waveMaker;
//boolean feeding;

//////////////////////////////////////////Define Pins/////////////////////////////////////////
////////////////////////////////////////////#PIN//////////////////////////////////////////////
// constants won't change. They're used here to 
// set pin numbers:
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
const int dht = 14;
const int lm = 15;
const int sumpHi = 16;
const int sumpLow = 17;
const int skimmerHi= 18;
//const int feeder = ;
//const int blueIn = ;
//const int blueOut = ;
//const int IR = ;

////////////////////////////////////////////Setup/////////////////////////////////////////////
//////////////////////////////////////////#SETUP//////////////////////////////////////////////
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
   pinMode(dht, INPUT);
   pinMode(lm, INPUT);
   pinMode(sumpHi, INPUT);
   pinMode(sumpLow, INPUT);
   pinMode(skimmerHi, INPUT);
   //pinMode(feeder, OUTPUT);//Feeding Stepper Motor
   //pinMode(blueIn, INPUT);//BlueTooth
   //pinMode(blueOut, OUTPUT);//BlueTooth
   //pinMode(IR, INPUT);//IR
}

//////////////////////////////////////////Loop////////////////////////////////////////////////
//////////////////////////////////////////#LOOP///////////////////////////////////////////////
void loop() {
    switch () {
      case 'a':    
        displayPumpsOn();//W/O Wavemaker
        break;
      case 'b':    
        waves();//W/Wavemaker
        break;
      case 'c':    
        test();//Test
        break;
      case 'd':    
        displayPumpsOff();//Water Change
        returnPumpOff();
        break;
      case 'e':    
        sumpOff();//Sump Maintenance
        break;
      case 'f':    
        displayPumpsOff();//Display Maintenance
        break;
      default:
        displayPumpsOn();//W/O Wavemaker
        break;
      } 
}

//////////////////////////////////////////Methods/////////////////////////////////////////////
//////////////////////////////////////////#METHODS////////////////////////////////////////////
void temp(){
  //Controls Heater
  //This isn't right
  //79 is Optimal
  if(displayWaterTemp <= 77.00){
  	heaterOn();
  }else if(displayWaterTemp >=  82.00){
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

void test(){
	//Turn all off
	allOff();
	whiteOff();
	actinicOff();
	moonlightOff();
	sumpOff();
	returnPumpOff();
	displayPumpLeftOn();
	delay(5000);
	displayPumpLeftOff();
	displayPumpRightOn();
	delay(5000);
	displayPumpRightOff();
	heaterOn();
	delay(5000);
	heaterOff();
	delay(5000);
	whiteOn();
	delay(5000);
	whiteOff();
	actinicOn();
	delay(5000);
	actinicOff();
	moonlightOn();
	delay(5000);
	moonlightOff();
	returnPumpOn();
	delay(5000);
	returnPumpOff();
	delay(5000);
	protienSkimmerOn();
	delay(5000);
	protienSkimmerOff();
	delay(5000);
	ultraVioletOn();
	delay(5000);
	ultraVioletOff;
	Serial.print("Test");
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
	digitalWrite(displayPumpLeft, HIGH;)
	Serial.print("Display pump left on");
}

void displayPumpRightOn(){
	digitalWrite(displayPumpRight, HIGH;)
	Serial.print("Display pump right on");
}

void displayPumpLeftOff(){
	digitalWrite(displayPumpLeft, LOW;)
	Serial.print("Display pump left off");
}

void displayPumpRightOff(){
	digitalWrite(displayPumpRight, LOW;)
	Serial.print("Display pump right off");
}

void heaterOn(){
	digitalWrite(heater, HIGH;)
	Serial.print("Heater on");
}

void heaterOff(){
	digitalWrite(heater, LOW;)
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
	digitalWrite(returnPump, HIGH;)
	Serial.print("Return pump on");
}

void returnPumpOff(){
	digitalWrite(returnPump, LOW;)
	Serial.print("Return pump off");
}

void protienSkimmerOn(){
	digitalWrite(proteinSkimmer, HIGH;)
	Serial.print("Protien skimmer on");
}

void protienSkimmerOff(){
	digitalWrite(proteinSkimmer, LOW;)
	Serial.print("Protien skimmer off");
}

void ultraVioletOn(){
	digitalWrite(uvPumpRelay, HIGH;)//Pump
	digitalWrite(uvLightRelay, HIGH;)//Light
	Serial.print("Ultra violet on");
}

void ultraVioletOff(){
	digitalWrite(uvPumpRelay, LOW;)//Pump
	digitalWrite(uvLightRelay, LOW;)//Light
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
        digitalWrite(alarm, HIGH;)//Speaker
        delay(1000)
        digitalWrite(alarm, LOW;)//Speaker
	Serial.print("Alert");
}

void alertButton(){//alert
        if alarmButton == True{
        digitalWrite(alarm, LOW;)//Speaker
        }
	Serial.print("Quiet alert speaker");
}

