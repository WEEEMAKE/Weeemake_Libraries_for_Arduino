
#ifndef WeLightSensor_H
#define WeLightSensor_H

#include "WePort.h"

class WeLightSensor
{
public:

  WeLightSensor(uint8_t port=0);

  int16_t read(void);
  
 private:
	uint8_t _Sensorpin;

};

#endif

