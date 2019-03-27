#include "WeELF328P.h"

WeWaterSensor water_sensor(PORT_A);

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	Serial.println(water_sensor.readAnalog());
	delay(100);
}