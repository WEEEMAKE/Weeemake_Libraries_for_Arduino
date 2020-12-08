#include "WeELF328P.h"
  
WeCompassSensor compass(PORT_A);

void setup()
{  
  Serial.begin(115200);
}
void loop() 
{
  int16_t head_X, head_Y, head_Z;
  compass.update();
  head_X = compass.getHeadX();
  head_Y = compass.getHeadY();
  head_Z = compass.getHeadZ();
  Serial.print("Compass:");
  Serial.println(head_X);
  delay(200);
}

