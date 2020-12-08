
#ifndef _WeBarometerSensor_H
#define _WeBarometerSensor_H

#include "WePort.h"

class WeBarometerSensor
{
public:

  WeBarometerSensor(uint8_t port=0);
  void reset(uint8_t port=0);
  float readHeight(void);
  float readPressure(void);
  float readTemp(void);
  
 private:
 	WeOneWire _WeBarometerSensor;
	uint8_t BarometerData[4];
    float height=1;
};

#endif

