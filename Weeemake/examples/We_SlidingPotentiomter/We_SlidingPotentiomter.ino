#include "WeELF328P.h"

WeSlidingPotentiomter SlidingPotentiomter(PORT_A);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
  Serial.print("Analog Value is: ");
  Serial.println(SlidingPotentiomter.readAnalog()); 
  delay(100);
}
