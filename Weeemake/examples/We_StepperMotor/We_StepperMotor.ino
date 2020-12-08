#include "WeELF328P.h"

WeStepperMotor stepperMotor(PORT_6);
void setup()
{  
  stepperMotor.setMicroStep(8);  //1,2,4,8,16,32
  stepperMotor.setSpeed(160);    //0-254
}
void loop() 
{ 
  stepperMotor.moveTo(1600);
  delay(3000);
  stepperMotor.moveTo(0);
  delay(3000);
}
