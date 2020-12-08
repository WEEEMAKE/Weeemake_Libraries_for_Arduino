#include "WeELF328P.h"

WeVibrationMotor motor(PORT_A);

void setup()
{  
}
void loop() 
{ 
    motor.run(50);  //0-100
    delay(1000);
    motor.stop();
    delay(1000);
}
