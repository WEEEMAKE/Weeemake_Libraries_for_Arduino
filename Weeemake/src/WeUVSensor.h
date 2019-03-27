
#ifndef _WeUVSensor_H
#define _WeUVSensor_H

#include "WePort.h"

class WeUVSensor
{
public:

  WeUVSensor(uint8_t port=0);
  void reset(uint8_t port=0);
  uint8_t readAnalog(void);
  uint8_t readIndex(void);

  
private:
	WeOneWire _WeUVSensor;
    volatile uint8_t  _Sensor1;
};

#endif

