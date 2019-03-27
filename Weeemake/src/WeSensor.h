
#ifndef WeSensor_H
#define WeSensor_H

#include <Arduino.h>

class WeSensor
{
public:
	WeSensor(uint8_t);
	void reset(uint8_t);
protected:
	uint8_t _SensorPin;
};

#endif

