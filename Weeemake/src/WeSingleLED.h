#ifndef WeSingleLED_H
#define WeSingleLED_H

#include "WePort.h"

class WeSingleLED
{
public:
	WeSingleLED(uint8_t port=0);
	void openLED();
	void closeLED();
private:
	uint8_t _Sensorpin;
};

#endif