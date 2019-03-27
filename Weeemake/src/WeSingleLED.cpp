#include "WeSingleLED.h"

WeSingleLED::WeSingleLED(uint8_t port)
{
	_Sensorpin = port;
	pinMode(_Sensorpin, OUTPUT);
}

void WeSingleLED::openLED()
{
	digitalWrite(_Sensorpin, HIGH);
}

void WeSingleLED::closeLED()
{
	digitalWrite(_Sensorpin, LOW);
}