Modified by Jared Anwyl
#include <dht.h>

//Set analog pin here
#define dht_dpin A0 //no ; here. Set equal to channel sensor is on

dht DHT;

void setup(){
Serial.begin(9600);
delay(300);//Let system settle
Serial.println("Temperature\n");
delay(700);//Wait rest of 1000ms recommended delay before
//accessing sensor
}//end "setup()"

void loop(){
//This is the "heart" of the program.
DHT.read11(dht_dpin);

Serial.print("temperature = ");
Serial.print(DHT.temperature);
Serial.print("C or ");
float fahrenheit = (((DHT.temperature * 9)/5)+32);
Serial.print(fahrenheit);
Serial.println("F ");
delay(800);//Don't try to access too frequently... in theory
//should be once per two seconds, fastest,
//but seems to work after 0.8 second.
}// end loop()

