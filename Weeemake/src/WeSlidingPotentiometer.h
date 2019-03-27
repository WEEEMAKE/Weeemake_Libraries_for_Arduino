
#ifndef _WeSlidingPotentiometer_H
#define _WeSlidingPotentiometer_H

#include "WePort.h"

class WeSlidingPotentiometer
{
public:

  WeSlidingPotentiometer(uint8_t port=0);
  void reset(uint8_t port=0);
  uint8_t readAnalog(void);

  
private:
	WeOneWire _WeSlidingPotentiometer;
    volatile uint8_t  _Sensor1;
};

#endif

