#include "WeELF328P.h"

WeLEDLineFollower lineFollower(PORT_A);

void setup()
{  
  Serial.begin(9600);
  lineFollower.closeLED();
}
void loop() 
{
  Serial.println(lineFollower.readSensor());
  delay(100);
}
