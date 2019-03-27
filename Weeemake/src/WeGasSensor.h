
#ifndef _WeGasSensor_H
#define _WeGasSensor_H

#include "WePort.h"

class WeGasSensor
{
public:

  WeGasSensor(uint8_t port=0);
  void reset(uint8_t port=0);
  void CloseLED(void);
  void OpenLED(void);
  uint8_t readAnalog(void);

  
private:
	WeOneWire _WeGasSensor;
    volatile uint8_t  _Sensor1;
};

#endif

