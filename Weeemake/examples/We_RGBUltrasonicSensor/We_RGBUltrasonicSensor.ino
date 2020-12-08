#include "WeELF328P.h"

WeUltrasonicSensor ultraSensor(PORT_B);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
  ultraSensor.setColor1(0,200,0);    //(Red,Green,Blue)
  ultraSensor.setColor2(200,0,0);    //(Red,Green,Blue)

  Serial.print("Distance : ");
  Serial.print(ultraSensor.distanceCm() );
  Serial.println(" cm");
  delay(100);
}
