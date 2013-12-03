/*
Jared Anwyl
Version 0.5 Alpha

I want to make this version stripped down
except for comments of future features
This is Psuedo Code/realcode for my aquarium controller

Version 1 will have 8 relays, rtc, lcd, floatswitches, temp guages, Water Sensor, Maybe 4 Relays and next version will have 4 more(?)
Version 2 will have bluetooth, 8 more relays, IR sensor/remote, wifi or ethernet (Probably Wifi), Bipolor Stepper Motor(4 wires)
Version 3 will have PH probe, ORP, D.O. (who knows if this will happen)

DHT11 is blue temp sensor
DS18B20 is Grove Sensor
DS18B20 is Waterproof Sensor (white = data, red = power, black = ground)  works with the latest downloadable "One Wire" library 
  Does not come with a pull-up resistor (4.7K), You can drop up to 5 sensors(unique address built into each) on a single Digital I/O point

I used Roger Reeds Aquarium Controller Code to reference
I possibly unintentionally copied some of his code
I stole the design of his autofeeder outright
Thanks Roger! Not only do you have a incredible controller but an incredible tank

This code is public domain

I need to rethink the heating/cooling
Alert Mode, Turn on Speaker till shut off Manually, Leak, Temp OOB, Salinity OOB, Send Email/Text
Figure out LCD
Figure out Case statement
Change Names for relays
DS1032 is RTC Model
2 plugs for display lights, 1 for moonlights, 1 for heater, 1 for return pump, 1 for protien, 2 for UV, 2 for display pumps
Gonna have/need 1 or 2 for fans, 1 for sump light
Digital: Relay, RTC, IR(TSOP 38)
Analog: Temperature
?: Bluetooth, LCD, Stepper Motor
*/

//Global Variables
float displayWaterTemp;
float currentTime;
boolean waveMaker;
boolean feeding;

//Define Pins
int relay_2 = 2;
int relay_3 = 3;
int relay_4 = 4;
int relay_5 = 5;
int relay_6 = 6;
int relay_7 = 7;
int relay_8 = 8;
int relay_1 = 9;
int rtcIn = 10;
int rtcOut = 11;
int lcd = 12;
int feeder = 13;
int blueIn = 14;
int blueOut = 15;
int IR = 16;


void setup() {
  Serial.begin(9600); 
   pinMode(2, OUTPUT);//Relay
   pinMode(3, OUTPUT);//Relay
   pinMode(4, OUTPUT);//Relay
   pinMode(5, OUTPUT);//Relay
   pinMode(6, OUTPUT);//Relay
   pinMode(7, OUTPUT);//Relay
   pinMode(8, OUTPUT);//Relay
   pinMode(9, OUTPUT);//Relay
   //pinMode(rtcIn, INPUT)//RTC
   //pinMode(rtcOut, OUTPUT)//RTC
   //pinMode(lcd, OUTPUT)//LCD
   //pinMode(feeder, OUTPUT)//Feeding Stepper Motor
   //pinMode(blueIn, INPUT)//BlueTooth
   //pinMode(blueOut, OUTPUT)//BlueTooth
   //pinMode(IR, INPUT)//IR
}

void loop() {
  // read the sensor:
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    // do something different depending on the character received.  
    // The switch statement expects single number values for each case;
    // in this exmaple, though, you're using single quotes to tell
    // the controller to get the ASCII value for the character.

    switch (inByte) {
    case 'a':    
      digitalWrite(2, HIGH);//W/O Wavemaker
      break;
    case 'b':    
      digitalWrite(3, HIGH);//W/Wavemaker
      break;
    case 'c':    
      digitalWrite(4, HIGH);//Test
      break;
    case 'd':    
      digitalWrite(5, HIGH);//Set RTC
      break;
    case 'e':    
      digitalWrite(6, HIGH);//Feed (All Display off)
      break;
    case 'f':    
      digitalWrite(7, HIGH);//Sump Maintenance
      break;
    case 'g':    
      digitalWrite(8, HIGH);//Display Maintenance
      break;
    case 'h':    
      digitalWrite(9, HIGH);//Water Change
      break;
    default:
      // turn all the LEDs off:
      for (int thisPin = 2; thisPin < 10; thisPin++) {
        digitalWrite(thisPin, LOW);
      }
    } 
  }
}

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
	Serial.print("test");
}

void feed(){
	if(feeding == true){
		//Stepper turns 360
		displayPumpsOff();
		delay(20000);
		displayPumpsOn();
	}
	Serial.print("feed");
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
	Serial.print("waves");
}

void allOn(){//Doesn't Turn all on i.e. lights
	displayPumpsOn();
	sumpOn();
	returnPumpOn();
	Serial.print("allOn");
}

void allOff(){//Doesn't Turn all off i.e. lights
	displayPumpsOff();
	sumpOff();
	returnPumpOff();
	Serial.print("allOff");
}
		
void displayPumpsOn(){
	displayPumpLeftOn();
	displayPumpRightOn();
	Serial.print("displayPumpsOn");
}

void displayPumpsOff(){
	displayPumpLeftOff();
	displayPumpRightOff();
	Serial.print("displayPumpsOff");
}

void displayPumpLeftOn(){
	//digitalWrite(, HIGH;)
	Serial.print("displayPumpLeftOn");
}

void displayPumpRightOn(){
	//digitalWrite(, HIGH;)
	Serial.print("displayPumpRightOn");
}

void displayPumpLeftOff(){
	//digitalWrite(, LOW;)
	Serial.print("displayPumpLeftOff");
}

void displayPumpRightOff(){
	//digitalWrite(, LOW;)
	Serial.print("displayPumpRightOff");
}

void heaterOn(){
	//digitalWrite(, HIGH;)
	Serial.print("heaterOn");
}

void heaterOff(){
	//digitalWrite(, LOW;)
	Serial.print("heaterOff");
}

void whiteOn(){
	//digitalWrite(, HIGH;)
	Serial.print("whiteOn");
}

void whiteOff(){
	//digitalWrite(, LOW;)
	Serial.print("whiteOff");
}

void actinicOn(){
	//digitalWrite(, HIGH;)
	Serial.print("actinicOn");
}

void actinicOff(){
	//digitalWrite(, LOW;)
	Serial.print("actinicOff");
}

void moonlightOn(){
	//digitalWrite(, HIGH;)
	Serial.print("moonlightOn");
}

void moonlightOff(){
	//digitalWrite(, LOW;)
	Serial.print("moonlightOff");
}

void returnPumpOn(){
	//digitalWrite(, HIGH;)
	Serial.print("returnPumpOn");
}

void returnPumpOff(){
	//digitalWrite(, LOW;)
	Serial.print("returnPumpOff");
}

void protienSkimmerOn(){
	//digitalWrite(, HIGH;)
	Serial.print("protienSkimmerOn");
}

void protienSkimmerOff(){
	//digitalWrite(, LOW;)
	Serial.print("protienSkimmerOff");
}

void ultraVioletOn(){
	//digitalWrite(, HIGH;)//Pump
	//digitalWrite(, HIGH;)//Light
	Serial.print("ultraVioletOn");
}

void ultraVioletOff(){
	//digitalWrite(, LOW;)//Pump
	//digitalWrite(, LOW;)//Light
	Serial.print("ultraVioletOff");
}

void sumpOn(){//all items but return pump
	ultraVioletOn();
	protienSkimmerOn();
	heaterOn();
	Serial.print("sumpOn");
}

void sumpOff(){//all items but return pump
	ultraVioletOff();
	protienSkimmerOff();
	heaterOff();
	Serial.print("sumpOff");
}

void alert(){//alert
        //digitalWrite(, HIGH;)//Speaker
        delay(1000)
        //digitalWrite(, LOW;)//Speaker
	Serial.print("Alert");
}
