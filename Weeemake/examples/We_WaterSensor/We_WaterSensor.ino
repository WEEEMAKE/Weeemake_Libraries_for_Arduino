#include "WeELF328P.h"

WeWaterSensor waterSensor(PORT_A);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
  Serial.print("Analog Value is: ");
  Serial.println(waterSensor.readAnalog()); 
  delay(100);
}
