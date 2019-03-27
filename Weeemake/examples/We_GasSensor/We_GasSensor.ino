#include "WeELF328P.h"

WeGasSensor GasSensor(PORT_A);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
  Serial.print("Analog Value is: ");
  Serial.println(GasSensor.readAnalog()); 
  delay(100);
}
