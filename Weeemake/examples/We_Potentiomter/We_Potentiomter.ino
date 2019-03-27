#include "WeELF328P.h"

WePotentiomter Potentiomter(PORT_A);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
  Potentiomter.OpenLED();
  Serial.print("Analog Value is: ");
  Serial.println(Potentiomter.readAnalog()); 
  delay(1000);
  Potentiomter.CloseLED();
  delay(1000);
}
