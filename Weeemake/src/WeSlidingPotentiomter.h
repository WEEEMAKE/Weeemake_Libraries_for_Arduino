
#ifndef _WeSlidingPotentiomter_H
#define _WeSlidingPotentiomter_H

#include "WePort.h"

class WeSlidingPotentiomter
{
public:

  WeSlidingPotentiomter(uint8_t port=0);
  void reset(uint8_t port=0);
  uint8_t readAnalog(void);

  
private:
	WeOneWire _WeSlidingPotentiomter;
    volatile uint8_t  _Sensor1;
};

#endif

