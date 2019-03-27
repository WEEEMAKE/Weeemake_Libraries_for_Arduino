#include "WeELF328P.h"
WeSoundSensor SoundSensor(PORT_3);
int value = 0; 
void setup() 
{
    Serial.begin(9600);
}
void loop()
{
  value = SoundSensor.read();
  Serial.print("value = ");
  Serial.println(value);
  delay(100);
}
