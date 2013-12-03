//Jared Anwyl
//Version 0.2 Alpha
//
//I want to make this version stripped down
//except for comments of future features
//This is Psuedo Code/realcode for my aquarium controller
//DHT11 is blue temp sensor
//DS18B20 is Grove Sensor
//DS18B20 is Waterproof Sensor (white = data, red = power, black = ground)  works with the latest downloadable "One Wire" library 
//  Does not come with a pull-up resistor (4.7K) but you can drop up to 5 of them (unique address built into each) on a single Digital I/O point
//Don't have, but stepper motor for autofeeder
//LCD for output display
//Remote and/or switches for mode changes
//RTC for keeping on/off times
//Relays to control on/off
//Need floatswitches for skimmer wasteoutput(video)
//Need another waterproof temp sensor for sump or maindisplay
//Need Wi-Fi Shield to post things on Internet
//I used Roger Reeds Aquarium Controller Code to reference
//I possibly unintentionally copied some of his code
//I stole the design of his autofeeder outright
//Thanks Roger!

//I need to rethink the heating/cooling
//Figure out fans
//Check Formatting

//////////////////////////////
//Define Constants
//////////////////////////////

//Booleans
boolean waveMaker = false;
boolean settings = false;
boolean feeding = false;
boolean sumpMaintenance = false;
boolean waterchange = false;
boolean displayMaintenance = false;
boolean test = false;

//Floats
float time;

//////////////////////////////
//Define Pins
//////////////////////////////

/*
//Actual Code
void setup()
{
 statements;
}

void loop()
{
 statements;
} 
*/

/*
//////////////////////////////
//Define Controllers Mode
//////////////////////////////
Switch(Mode){
   Case  0;
     lcd.print{Normal);//Everything but implemented wavemaker
     Break;
   Case  1;
     lcd.print{Normal W/Out wavemaker);//Everything
     Break;
   Case  2;
     lcd.print{Settings);//Setup settings like time and on/off
     Break;
   Case  3;
     lcd.print{Feeding);//If Feeding Display pumps off
     Break;
   Case  4;
     lcd.print{Sump Maintenance);//If sump Maintenance, Sump off
     Break;
   Case  5;
     lcd.print{Water Change);//If Water Change, Sump off, Alert off, Dosing off and return pump off
     Break;
   Case  6;
     lcd.print{Display Maintenance);//If Display Maintenance, Alert off
     Break;
   Case  7;
     lcd.print{Test);//Change Status every 5 Secs I.E. Actinic, 5 Secs Turn on White, 5 Secs Turn off White, 5 Secs turn off Actinic then normal lights and test next system
                     //Scroll through Heating and Cooling, Display light, Moonlight,  Fan, Monitors (Off then retake), Feeding, Alert, Wavemaker
                     //Don't test ATO, Saltwater or Dosing
     Break;
   }
*/

/*   
//Heating and Cooling system
//Controls Heater, Chiller (2 Relays)
//This isn't right heater would run till sump runs and back and forth
//79 is Optimal
if(waterTemp <= 77){
	heaterOn();
	chillerOff();
}else(temp >=  82){
	heaterOff();
	chillerOn();
}
*/

//Display Lighting System
//On/Off & Dim (Actinic, White, other LED control/color, 2+ Relays)
if(time == 11.00){
	actinicOn();
}else if(time == 12.00){
	whiteOn();
}else if(time == 20.00){
	whiteOff();
}else if(time == 21.00){
	actinicOff();
}

//Moonlight System (1 Relay)
//Socket for Moonlights
if(time == 21.59){
	moonlightOn();
}else if(time == 11.01){
	moonlightOff();
}
/*
//Fan System (1 Relay)
//Always on During Display Lighting System
//Adjust Voltage depending on Display lighting temp
//30% - 100%

//Always Display Temps, Salinity, Dosing Status & Graph Everything
//Display Last Dosing Date & Time
//Send over WiFi & Graph on Web Page
Hood Temp Monitor
Room Temp Monitor
Sump Temp Monitor
Display Temp Monitor
Sump Salinity
Dosing Status
PH
ORP
O2
Kalk
Alk
Ca
Nitrates
Nitrites
Ammonia
CO2 (Planted Tanks)
Last Read PAR
*/
//Sump On/Off (9 Relays)
//Return Pump On/Off
//Carbon Reactor On/Off
//Phosban Reactor On/Off
//Calcium Reactor On/Off
//Refugium Light On/Off
//Algae Turf Scrubber On/Off
// (Lights and Pump)
//U/V On/Off
//Protien Skimmer On/Off

//Feeding Mode
//Turn off Display Pumps
//Stepper Motor turns 360
Void feed(){
	if(feeding == true){
		displayPumpsOff();
		delay(20000);
		displayPumpsOn();
	}
}

void sumpLightOn(){
	digitalWrite(, HIGH;)
}

void sumpLightOff(){
	digitalWrite(, LOW;)
}

void skimmerOn(){
	digitalWrite(, HIGH;)
}

void skimmerOff(){
	digitalWrite(, LOW;)
}

//Wavemaker
Void waves(){
	while(waveMaker == true){//Check format
		displayLeftOn();
		displayRightOff();
		delay(20000);
		displayLeftOff();
		displayRightOn();
		delay(20000);
	}
}
		
Void displayPumpsOn(){
	displayPumpLeftOn();
	displayPumpRightOn();
}

Void displayPumpsOff(){
	displayPumpLeftOff();
	displayPumpRightOff();
}

Void displayPumpLeftOn(){
	digitalWrite(, HIGH;)
}

Void displayPumpRightOn(){
	digitalWrite(, HIGH;)
}

Void displayPumpLeftOff(){
	digitalWrite(, LOW;)
}

Void displayPumpRightOff(){
	digitalWrite(, LOW;)
}

Void heaterOn(){
	digitalWrite(, HIGH;)
}

Void heaterOff(){
	digitalWrite(, LOW;)
}

Void chillerOff(){
	digitalWrite(, LOW;)
}

Void chillerOn(){
	digitalWrite(, HIGH;)
}

Void whiteOn(){
	digitalWrite(, HIGH;)
}

Void whiteOff(){
	digitalWrite(, LOW;)
}

Void actinicOn(){
	digitalWrite(, HIGH;)
}

Void actinicOff(){
	digitalWrite(, LOW;)
}

Void moonlightOn(){
	digitalWrite(, HIGH;)
}

Void moonlightOff(){
	digitalWrite(, LOW;)
}

//Controls/Misc (relays)
//HOB On/Off

//Alert Mode
//Turn on Speaker till shut off Manually
//Leak
//Temp OOB
//Salinity OOB
//Send Email/Text

//Dosing System (2 Relays)
//Kalk
//Calcium
//Own Mix
