#include "WeELF328P.h"

WePIRSensor PIRSensor(PORT_A);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
  if(PIRSensor.readSensor())
  {
     Serial.println("People Motion Detected");
  }
   delay(100);
}
