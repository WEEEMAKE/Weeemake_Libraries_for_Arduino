#include "WeELF328P.h"
  
WeBarometerSensor barometer(PORT_A);
float Height,Pressure,Temp;
void setup()
{  
  Serial.begin(9600);
  barometer.setOrigin();
}
void loop() 
{
  Height=barometer.readRelativeHeight();
  Pressure=barometer.readPressure();
  Temp=barometer.readTemp();
  
  Serial.print("Height:");
  Serial.print(Height);
  Serial.print("  Pressure:");
  Serial.print(Pressure);
  Serial.print("  Temp:");
  Serial.println(Temp);
  delay(100);
}

