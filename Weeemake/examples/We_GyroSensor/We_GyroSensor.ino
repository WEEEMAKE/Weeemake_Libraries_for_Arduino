#include "WeELF328P.h"
  
WeGyroSensor gyro(PORT_A);

void setup()
{  
  Serial.begin(115200);
  gyro.begin();
}
void loop() 
{
  gyro.update();
  Serial.print("X:");
  Serial.print(gyro.getAngleX() );
  Serial.print(" Y:");
  Serial.print(gyro.getAngleY() );
  Serial.print(" Z:");
  Serial.println(gyro.getAngleZ() );
  delay(10);
}

