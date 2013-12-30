//Got Rid of EEPROM Menus (Need include for menu library)
//6 navi Pins Defined Ereased 2
//Made menus for switch statement
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
float ambientTempF=70.00;
float dTTempF=78.00;
float hoodTempF=100.00;

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
  menu.addUsrScreen(msc,10000);

  //(optional) create a splash screen (duration 5.000 millis)with some usefull infos the character \n marks end of LCD line 
  //(tip): use preallocated internal menu.sbuf buffer to save memory space!
//  sprintf(menu.sbuf,"MENWIZ TEST V %s\n.Free mem. :%d\n.Used mem  :%d\n.Lap secs  :%d",menu.getVer(),menu.freeRam(),mem-menu.freeRam(),5);
//  menu.addSplash((char *) menu.sbuf, 5000);
  }

void loop(){
  menu.draw(); 
  //PUT APPLICATION CODE HERE (if any)
  }
  
// user defined callbacks
// WARNING avoid sprintf usage: it requires > 1.5 kbytes of memory! 
void msc(){
  static  char buf[7];
  strcpy(menu.sbuf,"User screen"); //1st lcd line
  strcat(menu.sbuf,"\nUptime (s): ");strcat(menu.sbuf,itoa((int)(millis()/1000),buf,10));//2nd lcd line
  strcat(menu.sbuf,"\nFree mem  : ");strcat(menu.sbuf,itoa((int)menu.freeRam(),buf,10));//3rd lcd line
  strcat(menu.sbuf,"\n"); //4th lcd line (empty)
  menu.drawUsrScreen(menu.sbuf);
  }

/*
void msc(){
  static  char buf[7];
  //1st LCD Line
  strcpy(menu.sbuf,"Clock: ");//strcat(menu.sbuf,itoa((rtc.getTimeStr([FORMAT_SHORT])),buf,10));
  //2rd LCD Line
  strcat(menu.sbuf,"Ambient Temp: ");strcat(menu.sbuf,"\nF");
  //3rd LCD Line
  strcat(menu.sbuf,"Tank Temp: ");strcat(menu.sbuf,"\nF");
  //4th LCDLine
  strcat(menu.sbuf,"Hood Temp: ");strcat(menu.sbuf,"\nF");
  menu.drawUsrScreen(menu.sbuf);
}
*/
/*
void msc(){
    lcd.begin(20,4);               // initialize the lcd 
    lcd.backlight();
    lcd.home ();
    lcd.setCursor(0, 0);
    lcd.print("Clock:");
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