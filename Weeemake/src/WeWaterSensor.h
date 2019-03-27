
#ifndef _WeWaterSensor_H
#define _WeWaterSensor_H

#include "WePort.h"

class WeWaterSensor
{
public:

  WeWaterSensor(uint8_t port=0);
  void reset(uint8_t port=0);
  uint8_t readAnalog(void);

  
private:
	WeOneWire _WeWaterSensor;
    volatile uint8_t  _Sensor1;
};

#endif

