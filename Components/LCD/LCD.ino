/*
Constructor is what you need to focus on
Issues with libraries
*/
//10K pullup resistors for sda and SCL
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Addr: 0x3F, 20 chars & 4 lines
LiquidCrystal_I2C	lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE);

void setup()
{
    lcd.begin(20,4);               // initialize the lcd 
    lcd.backlight();
    lcd.home ();
    lcd.setCursor(0, 0);
    lcd.print("Ja");
}
void loop()
{

}
