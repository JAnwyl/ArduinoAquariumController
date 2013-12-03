//Jared Anwyl
//Version 0.4 Alpha
//
//I want to make this version stripped down
//except for comments of future features
//This is Psuedo Code/realcode for my aquarium controller

//DHT11 is blue temp sensor
//DS18B20 is Grove Sensor
//DS18B20 is Waterproof Sensor (white = data, red = power, black = ground)  works with the latest downloadable "One Wire" library 
//  Does not come with a pull-up resistor (4.7K), You can drop up to 5 sensors(unique address built into each) on a single Digital I/O point
//Need another waterproof temp sensor for sump or maindisplay
//Don't have, but stepper motor for autofeeder
//sain2004 LCD for output display
//Remote and/or switches for mode changes
//RTC for keeping on/off times
//Relays to control on/off
//Need floatswitches for skimmer wasteoutput(video)
//Need Wi-Fi Shield to post things on Internet

//I used Roger Reeds Aquarium Controller Code to reference
//I possibly unintentionally copied some of his code
//I stole the design of his autofeeder outright
//Thanks Roger! Not only do you have a incredible controller but a incredible tank

//I need to rethink the heating/cooling
//Figure out fans
//Check Formatting
//define pins
//write setup and loop

//1ST Version is going to have LCD, Relays, Temp Probes, RTC, Stepper Motor, Wi-Fi shield, Float Switch, Bluetooth

//////////////////////////////
//Define Variables
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
float waterTemp;
float airTemp;
float lightTemp;

//Integers
int button2State = 0;
int button3State = 0;
int button4State = 0;
int button5State = 0;
int button6State = 0;
int button7State = 0;
int button8State = 0;
int button9State = 0;

//////////////////////////////
//Define Pins
//////////////////////////////
const int buttonPin = 2; //Change to 4 pins to navigate a menu
const int buttonPin2 = 3; //2 Pins for scrolling through menu
const int buttonPin3 = 4; //2 Pins to select and go back
const int buttonPin4 = 5;
const int buttonPin5 = 6;
const int buttonPin6 = 7;
const int buttonPin7 = 8;
const int buttonPin8 = 9;
const int relayPin = 10;
const int relayPin2 = 11;
const int relayPin3 = 12;
const int relayPin4 = 13;
const int relayPin5 = 14;
const int relayPin6 = 15;
const int relayPin7 = 16;
const int relayPin8 = 17;

void setup()
{
 Serial.begin(9600); //will be LCD but monitor for testing
 
 // initialize the pushbutton pin as an input:
 pinMode(buttonPin, INPUT);
 pinMode(buttonPin2, INPUT);
 pinMode(buttonPin3, INPUT);
 pinMode(buttonPin4, INPUT);
 pinMode(buttonPin5, INPUT);
 pinMode(buttonPin6, INPUT);
 pinMode(buttonPin7, INPUT);
 pinMode(buttonPin8, INPUT);
 
 //initialize the relays as outputs
 pinMode(relayPin, OUTPUT);
 pinMode(relayPin2, OUTPUT);
 pinMode(relayPin3, OUTPUT);
 pinMode(relayPin4, OUTPUT);
 pinMode(relayPin5, OUTPUT);
 pinMode(relayPin6, OUTPUT);
 pinMode(relayPin7, OUTPUT);
 pinMode(relayPin8, OUTPUT);
   
}

void loop()
{
 button2State = digitalRead(buttonPin);
 button3State = digitalRead(buttonPin2);
 button4State = digitalRead(buttonPin3);
 button5State = digitalRead(buttonPin4);
 button6State = digitalRead(buttonPin5);
 button7State = digitalRead(buttonPin6);
 button8State = digitalRead(buttonPin7);
 button9State = digitalRead(buttonPin8);

/*
//The Loop should always check for button and remote presses
//If button pressed use appropriate switch case.
 if (button2State == HIGH) { 
    digitalWrite();  
  }
 if (button3State == HIGH) { 
    digitalWrite();  
  }
 if (button4State == HIGH) { 
    digitalWrite();  
  }
 if (button5State == HIGH) { 
    digitalWrite();  
  }
 if (button6State == HIGH) { 
    digitalWrite();  
  }
 if (button7State == HIGH) { 
    digitalWrite();  
  }
 if (button8State == HIGH) { 
    digitalWrite();  
  }
 if (button9State == HIGH) { 
    digitalWrite();  
  }
*/

} 



//////////////////////////////
//Define Controllers Mode
//////////////////////////////
Switch(Mode){
   case 0:
    lcd.print{Normal);//Everything
	allOn();
	waves();
    Break;
   case 1:
	allOn();
    lcd.print{Normal W/Out wavemaker);//Everything but implemented wavemaker
    Break;
   case 2:
    lcd.print{Settings);//Setup settings like time and on/off, haven't done this
    Break;
   case 3:
    lcd.print{Feeding);//If Feeding Display pumps off
	feed();
    Break;
   case 4:
    lcd.print{Sump Maintenance);//If sump Maintenance, Sump off, (keep return pump on)
	sumpOff();
    Break;
   case 5:
    lcd.print{Water Change);//If Water Change, Sump off, Alert off and return pump off
	sumpOff();
	returnPumpOff();
    Break;
   case 6:
    lcd.print{Display Maintenance);//If Display Maintenance, Alert off
    Break;
   case 7:
    lcd.print{Test);//Change Status every 5 Secs I.E. Actinic, 5 Secs Turn on White, 5 Secs Turn off White, 5 Secs turn off Actinic then normal lights and test next system
                     //Scroll through Heating and Cooling, Display light, Moonlight,  Fan, Monitors (Off then retake), Feeding, Alert, Wavemaker
                     //Don't test ATO, Saltwater or Dosing
    Break;
   default:
	lcd.print{Normal);//Everything
	allOn();
    Break;
   }

/*   
//Heating and Cooling system
//Controls Heater, Chiller (2 Relays)
//This isn't right heater would run till sump runs and back and forth
//79 is Optimal
if(waterTemp <= 77.00){
	heaterOn();
	chillerOff();
}else if(watertemp >=  82.00){
	heaterOff();
	chillerOn();
} else {
break;
}
*/

//Display Lighting System
//On/Off & Dim (Actinic, White, other LED control/color, 2+ Relays)
//setup dimming if get LEDs
if(time == 11.00){
	actinicOn();
}else if(time == 12.00){
	whiteOn();
}else if(time == 22.00){
	whiteOff();
}else if(time == 23.00){
	actinicOff();
}

//Moonlight System (1 Relay)
//Socket for Moonlights
if(time == 22.59){
	moonlightOn();
}else if(time == 11.01){
	moonlightOff();
}

//Fan System
//Always on During Display Lighting System
//Adjust Voltage depending on Display lighting temp
//30% - 100%

//Always Display Temps, Salinity, Dosing Status & Graph Everything
//Display Last Dosing Date & Time
//Send over WiFi & Graph on Web Page
/*
Hood Temp Monitor
Room Temp Monitor
Sump Temp Monitor
Display Temp Monitor
Sump Salinity
Last Read PAR
*/

//Test
Void test(){
	//Turn all off
	allOff();
	whiteOff();
	acitnicOff();
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
	refugiumLightOn();
	delay(5000);
	refugiumLightOff();
	protienSkimmerOn();
	delay(5000);
	protienSkimmerOff();
	delay(5000);
	ultraVioletOn();
	delay(5000);
	ultraViolentOff;
	Serial.print("test");
}

//Feeding Mode
Void feed(){
	if(feeding == true){
		//Stepper turns 360
		displayPumpsOff();
		delay(20000);
		displayPumpsOn();
	}
	Serial.print("feed");
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
		
Void displayPumpsOn(){
	displayPumpLeftOn();
	displayPumpRightOn();
	Serial.print("displayPumpsOn");
}

Void displayPumpsOff(){
	displayPumpLeftOff();
	displayPumpRightOff();
	Serial.print("displayPumpsOff");
}

Void displayPumpLeftOn(){
	//digitalWrite(, HIGH;)
	Serial.print("displayPumpLeftOn");
}

Void displayPumpRightOn(){
	//digitalWrite(, HIGH;)
	Serial.print("displayPumpRightOn");
}

Void displayPumpLeftOff(){
	//digitalWrite(, LOW;)
	Serial.print("displayPumpLeftOff");
}

Void displayPumpRightOff(){
	//digitalWrite(, LOW;)
	Serial.print("displayPumpRightOff");
}

Void heaterOn(){
	//digitalWrite(, HIGH;)
	Serial.print("heaterOn");
}

Void heaterOff(){
	//digitalWrite(, LOW;)
	Serial.print("heaterOff");
}

Void whiteOn(){
	//digitalWrite(, HIGH;)
	Serial.print("whiteOn");
}

Void whiteOff(){
	//digitalWrite(, LOW;)
	Serial.print("whiteOff");
}

Void actinicOn(){
	//digitalWrite(, HIGH;)
	Serial.print("actinicOn");
}

Void actinicOff(){
	//digitalWrite(, LOW;)
	Serial.print("actinicOff");
}

Void moonlightOn(){
	//digitalWrite(, HIGH;)
	Serial.print("moonlightOn");
}

Void moonlightOff(){
	//digitalWrite(, LOW;)
	Serial.print("moonlightOff");
}

Void returnPumpOn(){
	//digitalWrite(, HIGH;)
	Serial.print("returnPumpOn");
}

Void returnPumpOff(){
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

void ultraVioletOn(){//Light and Pump
	//digitalWrite(, HIGH;)
	//digitalWrite(, HIGH;)
	Serial.print("ultraVioletOn");
}

void ultraVioletOff(){//Light and Pump
	//digitalWrite(, LOW;)
	//digitalWrite(, LOW;)
	Serial.print("ultraVioletOff");
}

void sumpOn(){//all items but return pump
	refugiumLightOn();
	ultraVioletOn();
	protienSkimmerOn();
	heaterOn();
	Serial.print("sumpOn");
}

void sumpOff(){//all items but return pump
	refugiumLightOff();
	ultraVioletOff();
	protienSkimmerOff();
	heaterOff();
	Serial.print("sumpOff");
}

//Alert Mode
//Turn on Speaker till shut off Manually
//Leak
//Temp OOB
//Salinity OOB
//Send Email/Text

//Controls/Misc (relays)
//HOB On/Off
