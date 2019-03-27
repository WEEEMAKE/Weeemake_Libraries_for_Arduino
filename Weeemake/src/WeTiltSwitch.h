
#ifndef _WeTiltSwitch_H
#define _WeTiltSwitch_H

#include "WePort.h"

class WeTiltSwitch
{
public:

  WeTiltSwitch(uint8_t port=0);
  void reset(uint8_t port=0);

  uint8_t readSensor(void);
  bool readSensor(uint8_t);

  
private:
	WeOneWire _WeTiltSwitch;
    volatile uint8_t  _Sensor;
};

#endif

