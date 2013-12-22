// DS1302_Serial_Easy (C)2010 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// A quick demo of how to use my DS1302-library to 
// quickly send time and date information over a serial link
//
// I assume you know how to connect the DS1302.
// DS1302:  CE pin    -> Arduino Digital 2
//          I/O pin   -> Arduino Digital 3
//          SCLK pin  -> Arduino Digital 4

#include <DS1302.h>

// Init the DS1302
DS1302 rtc(2, 3, 4);

void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  
  // Setup Serial connection
  Serial.begin(9600);

  // The following lines can be commented out to use the values already stored in the DS1302
  rtc.setDOW(THURSDAY);        // Set Day-of-Week to THURSDAY
  rtc.setTime(20, 30, 0);     // Set the time to 8:30:00 (24hr format)
  rtc.setDate(19, 12, 2013);   // Set the date to December 19th, 2013
}

void loop()
{
  
  // Send date
  Serial.print(rtc.getDateStr([[FORMAT_SHORT]FORMAT_MIDDLEENDIAN]));
  Serial.print(" -- ");
  
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send time
  Serial.println(rtc.getTimeStr([FORMAT_SHORT]));
  
  // Wait one second before repeating :)
  delay (1000);
}
