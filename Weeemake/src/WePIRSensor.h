
#ifndef _WePIRSensor_H
#define _WePIRSensor_H

#include "WePort.h"

class WePIRSensor
{
public:

  WePIRSensor(uint8_t port=0);
  void reset(uint8_t port=0);

  uint8_t readSensor(void);

  
private:
	WeOneWire _WePIRSensor;
    volatile uint8_t  _Sensor;
};

#endif

