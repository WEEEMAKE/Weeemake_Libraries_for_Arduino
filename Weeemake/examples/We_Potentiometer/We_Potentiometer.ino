#include "WeELF328P.h"

WePotentiometer Potentiometer(PORT_A);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
  Potentiometer.OpenLED();
  Serial.print("Analog Value is: ");
  Serial.println(Potentiometer.readAnalog()); 
  delay(1000);
  Potentiometer.CloseLED();
  delay(1000);
}
