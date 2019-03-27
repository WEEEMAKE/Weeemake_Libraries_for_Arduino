#include "WeELF328P.h"

We130DCMotor motor(PORT_A);

int motorSpeed = 0;

void setup()
{  
}
void loop() 
{ 
  for(motorSpeed=50;motorSpeed<255;motorSpeed++)
  {
      motor.run(motorSpeed);
      delay(100);
  }
  motor.stop();
  delay(1000);
}
