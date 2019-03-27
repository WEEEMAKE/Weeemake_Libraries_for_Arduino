#include "WeELF328P.h"
WeLightSensor lightSensor(PORT_1);
int value = 0; 
void setup() 
{
    Serial.begin(9600);
}
void loop()
{
  value = lightSensor.read();
  Serial.print("value = ");
  Serial.println(value);
  delay(100);
}
