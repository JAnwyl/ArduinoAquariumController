//10K pullup resistors for sda and SCL
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Addr: 0x3F, 20 chars & 4 lines
//0x27 worked for other poster
LiquidCrystal_I2C lcd(0x3F); 

void setup()
{
    lcd.begin(20,4);               // initialize the lcd 
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Hello");
}
void loop()
{

}
