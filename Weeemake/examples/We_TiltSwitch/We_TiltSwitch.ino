#include "WeELF328P.h"

WeTiltSwitch tiltSwitch(PORT_A);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
  uint8_t s1;
  s1=tiltSwitch.readSensor();
  if (s1==1)
  {
    Serial.println("Tilt Right");
  }
  else if (s1==2)
  {
    Serial.println("Tilt Left");
  }
  delay(100);
}
