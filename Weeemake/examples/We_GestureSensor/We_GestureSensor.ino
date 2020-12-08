#include "WeELF328P.h"

WeGestureSensor GestureSensor(PORT_A);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{   
  uint8_t value=GestureSensor.read();
  switch(value)
  {
     case 1: Serial.println("Right"); break;
     case 2: Serial.println("Forward"); break;
     case 3: Serial.println("Left"); break;
     case 4: Serial.println("Back"); break;
     case 5: Serial.println("Down"); break;
   }
  delay(100);
}
