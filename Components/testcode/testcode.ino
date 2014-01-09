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
boolean soundAlarm;
String AmPm;

int      tp=0;//Menu

const int piezo = 13; //Alarm Piezo
// DEFINE ARDUINO PINS FOR THE NAVIGATION BUTTONS
#define UP_BUTTON_PIN       26
#define DOWN_BUTTON_PIN     27
#define CONFIRM_BUTTON_PIN  28
#define ESCAPE_BUTTON_PIN   29

menwiz menu;
//Addr: 0x3F, 20 chars & 4 lines
LiquidCrystal_I2C	lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE);

DS1302 rtc(10, 11, 12); //10,11,12 Are RTC pins

void setup() {
  rtc.halt(false);              // Set the clock to run-mode
  _menu *r,*s1,*s2;             //Menu
  menu.begin(&lcd,20,4);        // inizialize the menu object (20 colums x 4 rows)
  
  Serial.begin(9600);
  pinMode(piezo, OUTPUT);//Alarm Piezo
  //create the menu tree
  r=menu.addMenu(MW_ROOT,NULL,F("MAIN MENU"));
    s1=menu.addMenu(MW_SUBMENU,r,F("Settings"));
      s2=menu.addMenu(MW_VAR,s1,F("Set RTC"));
        s2->addVar(MW_LIST,&tp);
        s2->addItem(MW_LIST,F("Day of Week"));
        s2->addItem(MW_LIST,F("24 Hour"));
        s2->addItem(MW_LIST,F("Min"));
        s2->addItem(MW_LIST,F("Year"));
      s2=menu.addMenu(MW_VAR,s1,F("Lighting"));
        s2->addVar(MW_LIST,&tp);
        s2->addItem(MW_LIST,F("On"));
        s2->addItem(MW_LIST,F("Off"));
      s2=menu.addMenu(MW_VAR,s1,F("Moon Lights"));
        s2->addVar(MW_LIST,&tp);
        s2->addItem(MW_LIST,F("On"));
        s2->addItem(MW_LIST,F("Off"));

    s1=menu.addMenu(MW_VAR,r,F("W/Wavemaker"));
      s1->addVar(MW_ACTION,waves);
          
  menu.navButtons(UP_BUTTON_PIN,DOWN_BUTTON_PIN,ESCAPE_BUTTON_PIN,CONFIRM_BUTTON_PIN);

  menu.addUsrScreen(usrScreen,10000);
}

void loop() {
  menu.draw();
  alarm(); 
}

void setLightsOn(){
}

void setActnicOn(){
}

void setMoonlightsOn(){
}

void setLightsOff(){
}

void setActnicOff(){
}

void setMoonlightsOff(){
}

void setDayOfWeek(){
}

void setCalenderDate(){
}

void setTimeOfDay(){
}

void setYear(){
}

void alarm(){
  
}

void waves(){
  Serial.println("waves"); 
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
    digitalWrite(piezo,HIGH);
    delayMicroseconds(period / 2);
    digitalWrite(piezo, LOW);
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

void usrScreen(){
  static  char buf[7];
  //1st LCD Line
  strcpy(menu.sbuf,"Clock: ");
    //strcat(menu.sbuf,rtc.getTimeStr[FORMAT_SHORT]);
  //2rd LCD Line
  strcat(menu.sbuf,"Air Temp: ");
    //strcat(menu.sbuf,dtostrf(ambientTempF, 5, 2, buf));
    strcat(menu.sbuf,"\nF");
  //3rd LCD Line
  strcat(menu.sbuf,"Tank Temp: ");
    //strcat(menu.sbuf,dtostrf(dTTempF, 5, 2, buf));
    strcat(menu.sbuf,"\nF");
  //4th LCDLine
  strcat(menu.sbuf,"Hood Temp: ");
    //strcat(menu.sbuf,dtostrf(hoodTempF, 5, 2, buf));
    strcat(menu.sbuf,"\nF");
    
  menu.drawUsrScreen(menu.sbuf);
}
