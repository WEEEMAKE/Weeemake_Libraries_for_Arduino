#include "WeSensor.h"

WeSensor::WeSensor(uint8_t pin)
{
	_SensorPin = pin;
}

void WeSensor::reset(uint8_t pin)
{
	_SensorPin = pin;
}
