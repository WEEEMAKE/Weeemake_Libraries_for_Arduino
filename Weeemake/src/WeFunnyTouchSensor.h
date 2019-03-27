
#ifndef _WeFunnyTouchSensor_H
#define _WeFunnyTouchSensor_H

#include "WePort.h"

class WeFunnyTouchSensor
{
public:

  WeFunnyTouchSensor(uint8_t port=0);
  void reset(uint8_t port=0);

  uint8_t readValue(void);
  
private:
	WeOneWire _WeFunnyTouchSensor;
    volatile uint8_t  _Sensor1;
};

#endif

