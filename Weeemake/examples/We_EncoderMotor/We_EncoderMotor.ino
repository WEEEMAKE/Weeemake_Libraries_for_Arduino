#include "WeELF328P.h"
// WeEncoderMotor motor2(PORT_3);
WeEncoderMotor motor1(PORT_6);
WeDCMotor motor3(M9);
WeDCMotor motor4(M10);

uint8_t motorSpeed = 255;
void setup()
{  
  Serial.begin(115200);
  delay(2000);
  motor1.setPositionOrigin();
  motor1.runSpeed(motorSpeed);
  delay(2000);
    // motor2.runSpeed(motorSpeed);
  motor1.run(-motorSpeed);
  delay(2000);
  motor1.moveTo(motorSpeed,585);
  delay(1000);

}

void loop() 
{
  // Serial.println(motor1.getCurrentPosition());
  // motor1.moveTo(motorSpeed,585);
  // // motor3.run(255);
  // // motor4.run(255);
  delay(3000);
  
  // Serial.println(motor1.getCurrentPosition());
  // motor1.moveTo(motorSpeed,1);
  // // motor3.run(-255);
  // // motor4.run(-255);
  delay(3000);
    // motor1.run(-motorSpeed);
    // motor2.run(motorSpeed);
    // delay(10);
}
