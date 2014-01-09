#include <Wire.h> //LCD & Menu
#include <LiquidCrystal_I2C.h> //LCD & Menu
#include <LCD.h> //Menu
#include <DS1302.h> //RTC
#include <buttons.h> //Menu
#include <EEPROM.h> //Menu
#include <MENWIZ.h> //Menu

int      tp=0;//Menu
int      lp=0;//Menu
int      mp=0;//Menu
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
  _menu *r,*s1,*s2,*s3;             //Menu
  menu.begin(&lcd,20,4);        // inizialize the menu object (20 colums x 4 rows)
  
  Serial.begin(9600);
  //create the menu tree
  r=menu.addMenu(MW_ROOT,NULL,F("MAIN MENU"));
    s1=menu.addMenu(MW_SUBMENU,r,F("Settings"));
      s2=menu.addMenu(MW_VAR,s1,F("Set RTC"));
        s2->addVar(MW_LIST,&tp);
        s2->addItem(MW_LIST,F("Day of Week"));
          s3->addVar(MW_ACTION,setDayOfWeek);
        s2->addItem(MW_LIST,F("24 Hour"));
          s3->addVar(MW_ACTION,setTwentyFourHour);
        s2->addItem(MW_LIST,F("Min"));
          s3->addVar(MW_ACTION,setMin);
        s2->addItem(MW_LIST,F("Year"));
          s3->addVar(MW_ACTION,setYear);
      s2=menu.addMenu(MW_VAR,s1,F("Lighting"));
        s2->addVar(MW_LIST,&lp);
        s2->addItem(MW_LIST,F("On"));
        s2->addItem(MW_LIST,F("Off"));
      s2=menu.addMenu(MW_VAR,s1,F("Moon Lights"));
        s2->addVar(MW_LIST,&mp);
        s2->addItem(MW_LIST,F("On"));
        s2->addItem(MW_LIST,F("Off"));

    s1=menu.addMenu(MW_VAR,r,F("W/Wavemaker"));
      s1->addVar(MW_ACTION,waves);
          
  menu.navButtons(UP_BUTTON_PIN,DOWN_BUTTON_PIN,ESCAPE_BUTTON_PIN,CONFIRM_BUTTON_PIN);
}

void loop() {
  menu.draw();
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
  Serial.println("SetDOW");
}

void setMin(){
  Serial.println("SetMinute");
}

void setTwentyFourHour(){
  Serial.println("SetTwentyFour");
}

void setYear(){
  Serial.println("SetYear");
}

void alarm(){
  
}

void waves(){
  Serial.println("waves"); 
}

void getRTC(){
  rtc.getTimeStr(2);
}

