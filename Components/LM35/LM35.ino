/*
Modified by Jared Anwyl
LM35 Pin 1 (Vss) –> Arduino +5V
LM35 Pin 2 (Signal) –> Arduino Pin 0 
LM35 Pin 2 (Signal) –> Arduino Gnd via Resistor 4.7K
LM35 Pin 3 (GND) –> Arduino Ground
*/

float temp, tempf;
//Set pin here
int tempPin = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  temp = analogRead(tempPin);
  temp = temp * 0.48828125;
  Serial.print("TEMPRATURE = ");
  Serial.print(temp);
  Serial.print("*C ");
  tempf = (temp * 9)/ 5 + 32;
  Serial.print(tempf);
  Serial.print("*F");
  Serial.println();
  delay(1000);
}
