/*
Modified by Jared Anwyl
seems as though this sensor only changes 1 deg Celsius at a time
because of the 1 deg its not very accurate
DHT11 Pin 1 (Vss) –> Arduino +5V
DHT11 Pin 2 (Signal) –> Arduino Pin 2
DHT11 Pin 2 (Signal) –> Arduino +5V via Resistor 4.7K
DHT11 Pin 3 –> N/C
DHT11 Pin 4 (GND) –> Arduino Ground
*/

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

