#include "WeELF328P.h"

WeUVSensor uvSensor(PORT_A);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
  Serial.print("Analog Value is: ");
  Serial.println(uvSensor.readAnalog()); 
  delay(100);
}
