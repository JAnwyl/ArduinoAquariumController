//dtostrf Double to String
//dtostre Double to String
//itoa Int to String
//Got Rid of EEPROM Menus (Need include for menu library)
//6 navi Pins Defined Ereased 2
//Made menus for switch statement
#include <FormatDouble.h>
//MENWIZ ESAMPLE
#include <Wire.h>
//INSERT ALL THE FOLLOWING 5 INCLUDES AFTER INCLUDING WIRE LIB 
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <buttons.h>
#include <EEPROM.h>
#include <MENWIZ.h>

// DEFINE ARDUINO PINS FOR THE NAVIGATION BUTTONS
#define UP_BUTTON_PIN       26
#define DOWN_BUTTON_PIN     27
#define CONFIRM_BUTTON_PIN  28
#define ESCAPE_BUTTON_PIN   29

//Create global object menu and lcd
menwiz menu;
LiquidCrystal_I2C	lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE);

//instantiate global variables to bind to menu
int      tp=0;

double temp=76.00;
String ambientTemp[]="70.00";
//chars work and are segmented below (I need to convert a double to a char)
char ambientTempF[]="70.00";
char dTTempF[]="78.00";
char hoodTempF[]="100.00";

void setup(){
  _menu *r,*s1,*s2;
  int  mem;

  Serial.begin(9600);
  
  // have a look on memory before menu creation
  Serial.println(sizeof(menwiz));
  mem=menu.freeRam();

  // inizialize the menu object (20 colums x 4 rows)
  menu.begin(&lcd,20,4);

  //create the menu tree
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

  //declare navigation buttons (required)
  menu.navButtons(UP_BUTTON_PIN,DOWN_BUTTON_PIN,ESCAPE_BUTTON_PIN,CONFIRM_BUTTON_PIN);

  //(optional)create a user define screen callback to activate after 10 secs (10.000 millis) since last button push 
  menu.addUsrScreen(msc,2000);

  //(optional) create a splash screen (duration 5.000 millis)with some usefull infos the character \n marks end of LCD line 
  //(tip): use preallocated internal menu.sbuf buffer to save memory space!
//  sprintf(menu.sbuf,"MENWIZ TEST V %s\n.Free mem. :%d\n.Used mem  :%d\n.Lap secs  :%d",menu.getVer(),menu.freeRam(),mem-menu.freeRam(),5);
//  menu.addSplash((char *) menu.sbuf, 5000);
  }

void loop(){
  menu.draw(); 
  //PUT APPLICATION CODE HERE (if any)
  //dTemp=fmtDouble(dTTempF, 6, buf, sizeof buf);
  }

/*  
// user defined callbacks
// WARNING avoid sprintf usage: it requires > 1.5 kbytes of memory!
//This is demo that works
void msc(){
  static  char buf[7];
  strcpy(menu.sbuf,"User screen"); //1st lcd line
  strcat(menu.sbuf,"\nUptime (s): ");strcat(menu.sbuf,itoa((int)(millis()/1000),buf,10));//2nd lcd line
  strcat(menu.sbuf,"\nFree mem  : ");strcat(menu.sbuf,itoa((int)menu.freeRam(),buf,10));//3rd lcd line
  strcat(menu.sbuf,"\n"); //4th lcd line (empty)
  menu.drawUsrScreen(menu.sbuf);
  }
*/

///*
void msc(){
  char buffer[6];

  //1st LCD Line
  strcpy(menu.sbuf,"Clock: ");
    //strcat(menu.sbuf,rtc.getTimeStr([FORMAT_SHORT]));
    
  //2rd LCD Line
  strcat(menu.sbuf,"\nAmbient Temp:");
    //Below Compiles but only shows clock and turns off backlight
    //strcat(menu.sbuf,dtostrf(dTTempF, 6, 2, buffer));
    //strcat(menu.sbuf,dtostre(dTTempF, 6, 2, buffer));
    strcat(menu.sbuf,ambientTempF);
    //strcat(menu.sbuf,fmtDouble(ambientTemp, 5, buf, sizeof buf));
    strcat(menu.sbuf,"F");
    
  //3rd LCD Line
  strcat(menu.sbuf,"\nTank Temp:");
    strcat(menu.sbuf,dTTempF);
    strcat(menu.sbuf,"F");
    
  //4th LCDLine
  strcat(menu.sbuf,"\nHood Temp:");
    strcat(menu.sbuf,hoodTempF);
    strcat(menu.sbuf,"F");
    
  menu.drawUsrScreen(menu.sbuf);
}
//*/

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
  Serial.println("Display Maintenance");
}
