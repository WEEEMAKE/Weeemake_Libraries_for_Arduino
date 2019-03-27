#include "WeLimitSwitch.h"

WeLimitSwitch::WeLimitSwitch(uint8_t port)
{
  reset(port);
}

void WeLimitSwitch::reset(uint8_t port)
{
	_Sensorpin = port;
	pinMode(_Sensorpin, INPUT);
}

bool WeLimitSwitch::read(void)
{
   return digitalRead(_Sensorpin);
}





