#include "WeELF328P.h"
WeEncoderMotor motor1(PORT_3);

uint8_t motorSpeed = 100;
void setup()
{  
  Serial.begin(9600);
  delay(2000);
  motor1.setPositionOrigin();
}

void loop() 
{
  Serial.println(motor1.getCurrentPosition());
  motor1.moveTo(motorSpeed,585);
  delay(3000);
  
  Serial.println(motor1.getCurrentPosition());
  motor1.moveTo(motorSpeed,1);
  delay(3000);
}
