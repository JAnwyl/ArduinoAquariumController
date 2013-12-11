float temp, tempf;
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
