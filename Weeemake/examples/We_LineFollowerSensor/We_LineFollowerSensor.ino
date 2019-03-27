#include "WeELF328P.h"
// #include "WeELFMini.h"

WeLineFollower lineFollower(PORT_A);

void setup()
{  
  Serial.begin(115200);
}
void loop() 
{
  uint16_t s1,s2;
  lineFollower.startRead();
  s1=lineFollower.readSensor1();
  s2=lineFollower.readSensor2();
  Serial.print("S1=");
  Serial.println(s1);
  Serial.print("S2=");
  Serial.println(s2);
  delay(100);
}
