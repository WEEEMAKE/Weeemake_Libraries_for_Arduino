
#ifndef WeSoundSensor_H
#define WeSoundSensor_H

#include "WePort.h"

class WeSoundSensor
{
public:
	WeSoundSensor(uint8_t port=0);

	uint16_t read(void);
  
private:
	uint8_t _Sensorpin;
};

class WeSoundSensor_RJ
{
public:
	WeSoundSensor_RJ(uint8_t port=0);
	void reset(uint8_t port=0);

	uint16_t read(void);

private:
	WeOneWire _WeSoundSensor_RJ;
};

#endif

