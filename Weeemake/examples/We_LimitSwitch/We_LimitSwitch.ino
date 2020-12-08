#include "WeELF328P.h"
WeLimitSwitch limitSwitch(PORT_A);
void setup() 
{
    Serial.begin(9600);
}
void loop()
{
  if(limitSwitch.read()==1)
  {
    Serial.println("limitSwitch DOWN");
  }
  delay(100);
}
