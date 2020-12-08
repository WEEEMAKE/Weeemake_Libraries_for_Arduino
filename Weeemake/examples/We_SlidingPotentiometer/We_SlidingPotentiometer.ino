#include "WeELF328P.h"

WeSlidingPotentiometer SlidingPotentiometer(PORT_A);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
  Serial.print("Analog Value is: ");
  Serial.println(SlidingPotentiometer.readAnalog()); 
  delay(100);
}
