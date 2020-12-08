#include "WeELF328P.h"

WeFlameSensor flame(PORT_A);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
  uint8_t d1,d2,d3;
  flame.readData();
  d1=flame.showSensor1();
  d2=flame.showSensor2();
  d3=flame.showSensor3();
  Serial.print(d1);
  Serial.print(",");
  Serial.print(d2);
  Serial.print(",");
  Serial.println(d3);
  delay(100);
}
