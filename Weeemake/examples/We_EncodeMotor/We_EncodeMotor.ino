#include "WeELF328P.h"

WeEncoderMotor motor(PORT_3);

void setup()
{
	
}

void loop()
{
	motor.run(150);
	delay(1000);
	motor.run(-150);
	delay(1000);
}