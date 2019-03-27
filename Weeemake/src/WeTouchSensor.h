
#ifndef _WeTouchSensor_H
#define _WeTouchSensor_H

#include "WePort.h"

class WeTouchSensor
{
public:

  WeTouchSensor(uint8_t port=0);
  void reset(uint8_t port=0);
  uint8_t touched(void);
  void setMode(uint8_t value);
  
private:
	WeOneWire _WeTouchSensor;
    volatile uint8_t  _Sensor1;
};

#endif

