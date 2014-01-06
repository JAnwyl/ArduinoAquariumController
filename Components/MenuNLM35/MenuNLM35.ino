/*
Modified by Jared Anwyl
LM35 Pin 1 (Vss) –> Arduino +5V
LM35 Pin 2 (Signal) –> Arduino Pin 0 
LM35 Pin 2 (Signal) –> Arduino Gnd via Resistor 4.7K
LM35 Pin 3 (GND) –> Arduino Ground
*/
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <buttons.h>
#include <EEPROM.h>
#include <MENWIZ.h>

#define UP_BUTTON_PIN       26
#define DOWN_BUTTON_PIN     27
#define CONFIRM_BUTTON_PIN  28
#define ESCAPE_BUTTON_PIN   29

menwiz menu;
LiquidCrystal_I2C	lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE);

float temp, tempf;
//Set pin here
int tempPin = 0;

int tp=0;
float dTTemp=68.00;
float hoodTemp;
char ambientTempF[]="70.00";
char dTTempF[]="78.00";
char hoodTempF[]="100.00";

void setup(){
  _menu *r,*s1,*s2;

  Serial.begin(9600);

  menu.begin(&lcd,20,4);

  r=menu.addMenu(MW_ROOT,NULL,F("MAIN MENU"));
    s1=menu.addMenu(MW_SUBMENU,r,F("Settings"));
      s2=menu.addMenu(MW_VAR,s1,F("Set RTC"));
        s2->addVar(MW_LIST,&tp);
          s2->addItem(MW_LIST,F("Day of Week"));
          s2->addItem(MW_LIST,F("Hour"));
          s2->addItem(MW_LIST,F("Min"));
          s2->addItem(MW_LIST,F("Year"));

    s1=menu.addMenu(MW_VAR,r,F("W/Wavemaker"));
      s1->addVar(MW_ACTION,wave);
      s1->setBehaviour(MW_ACTION_CONFIRM,false);
      
    s1=menu.addMenu(MW_VAR,r,F("W/O Wavemaker"));
      s1->addVar(MW_ACTION,wowaves);
      s1->setBehaviour(MW_ACTION_CONFIRM,false);
      
    s1=menu.addMenu(MW_VAR,r,F("Waterchange"));
      s1->addVar(MW_ACTION,water);
      s1->setBehaviour(MW_ACTION_CONFIRM,false);
      
    s1=menu.addMenu(MW_VAR,r,F("Sump Maintenance"));
      s1->addVar(MW_ACTION,sump);
      s1->setBehaviour(MW_ACTION_CONFIRM,false);
      
    s1=menu.addMenu(MW_VAR,r,F("Display Maintenance"));
      s1->addVar(MW_ACTION,display);
      s1->setBehaviour(MW_ACTION_CONFIRM,false);

  menu.navButtons(UP_BUTTON_PIN,DOWN_BUTTON_PIN,ESCAPE_BUTTON_PIN,CONFIRM_BUTTON_PIN);

  menu.addUsrScreen(msc,2000);
  }

void loop(){
  temp = analogRead(tempPin); //Lm35
  temp = temp * 0.48828125; //Lm35
  tempf = (temp * 9)/ 5 + 32; //Lm35 conversion to Farenheit
  menu.draw();
  }

void msc(){
  char buffer[6];

  //1st LCD Line
  strcpy(menu.sbuf,"Clock: ");
    
  //2rd LCD Line
  strcat(menu.sbuf,"\nAir Temp:");
    strcat(menu.sbuf,dtostrf(tempf, 5, 2, buffer));
    strcat(menu.sbuf,"F");
    
  //3rd LCD Line
  strcat(menu.sbuf,"\nTank Temp:");
    strcat(menu.sbuf,dtostrf(dTTemp, 6, 2, buffer));
    //strcat(menu.sbuf,dTTempF);
    strcat(menu.sbuf,"F");
    
  //4th LCDLine
  strcat(menu.sbuf,"\nHood Temp:");
    strcat(menu.sbuf,hoodTempF);
    strcat(menu.sbuf,"F");
    
  menu.drawUsrScreen(menu.sbuf);
}

void wave(){
  Serial.println("Wavemaker");
}

void wowaves(){
  Serial.println("W/O Wavemaker");
}
 
void water(){
  Serial.println("Waterchange");
}

void sump(){
  Serial.println("Sump Maintenance");
}

void display(){
  Serial.println("Display Tank Maintenance");
}
