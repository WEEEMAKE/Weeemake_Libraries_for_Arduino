#include "WeELFMini.h"
WeAdapter adapter(PORT_A);
void setup() 
{
  Serial.begin(9600);
}
void loop()
{
  adapter.write(1,60);
  adapter.RGBshow(2,0,10,10,10);
  Serial.println(adapter.readTemperature(3));
  adapter.digitalWrite(4,HIGH);
  //Serial.println(adapter.digitalRead(1));
  //Serial.println(adapter.analogRead(1)); 
  delay(1000);
  adapter.write(1,120);
  adapter.RGBshow(2,0,0,0,0);
  Serial.println(adapter.readTemperature(3));
  adapter.digitalWrite(4,LOW);
  delay(1000);
}
