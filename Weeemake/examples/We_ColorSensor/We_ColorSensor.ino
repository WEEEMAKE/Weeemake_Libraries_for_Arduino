#include "WeELF328P.h"
  
WeColorSensor colorSensor(PORT_A);

uint16_t Redvalue;
uint16_t Greenvalue;
uint16_t Bluevalue;
uint16_t Colorvalue;

void setup()
{  
  Serial.begin(9600);
  colorSensor.whitebalance();
}
void loop() 
{
  colorSensor.readColorData();
  
  Redvalue=colorSensor.showRedData();
  Greenvalue=colorSensor.showGreenData();
  Bluevalue=colorSensor.showBlueData();
  Colorvalue=colorSensor.showColorData();
  Serial.print("R:");
  Serial.print(Redvalue );
  Serial.print("  G:");
  Serial.print(Greenvalue);
  Serial.print("  B:");
  Serial.print(Bluevalue);
  Serial.print("  C:");
  Serial.println(Colorvalue);
  delay(200);
}

