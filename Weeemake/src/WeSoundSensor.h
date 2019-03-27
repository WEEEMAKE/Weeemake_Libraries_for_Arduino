
#ifndef WeSoundSensor_H
#define WeSoundSensor_H

#include "WePort.h"


class WeSoundSensor
{
public:

  WeSoundSensor(uint8_t port=0);

  int16_t read(void);
  
 private:
	uint8_t _Sensorpin;

};

#endif

