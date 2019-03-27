#include "WeELF328P.h"

WeUltrasonicSensor ultraSensor(PORT_C);

void setup()
{  
  Serial.begin(9600);
}
void loop() 
{
	uint8_t value = random(0,256);
  ultraSensor.setColor1(value,value,value);    //(Red,Green,Blue)
  ultraSensor.setColor2(value,value,value);    //(Red,Green,Blue)
  Serial.print("Distance : ");
  Serial.print(ultraSensor.distanceCm() );
  Serial.println(" cm");
  delay(500);
  // ultraSensor.setColor1(0,100,0);    //(Red,Green,Blue)
  // ultraSensor.setColor2(0,100,0);    //(Red,Green,Blue)
  // Serial.print("Distance : ");
  // Serial.print(ultraSensor.distanceCm() );
  // Serial.println(" cm");
  // delay(500);
  // ultraSensor.setColor1(0,0,100);    //(Red,Green,Blue)
  // ultraSensor.setColor2(0,0,100);    //(Red,Green,Blue)
  // Serial.print("Distance : ");
  // Serial.print(ultraSensor.distanceCm() );
  // Serial.println(" cm");
  // delay(500);
  // ultraSensor.setColor1(0,100,100);    //(Red,Green,Blue)
  // ultraSensor.setColor2(0,100,100);    //(Red,Green,Blue)
  // Serial.print("Distance : ");
  // Serial.print(ultraSensor.distanceCm() );
  // Serial.println(" cm");
  // delay(500);
  // ultraSensor.setColor1(100,0,100);    //(Red,Green,Blue)
  // ultraSensor.setColor2(100,0,100);    //(Red,Green,Blue)
  // Serial.print("Distance : ");
  // Serial.print(ultraSensor.distanceCm() );
  // Serial.println(" cm");
  // delay(500);
}
