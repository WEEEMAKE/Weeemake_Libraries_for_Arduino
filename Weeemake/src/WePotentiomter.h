
#ifndef _WePotentiomter_H
#define _WePotentiomter_H

#include "WePort.h"

class WePotentiomter
{
public:

  WePotentiomter(uint8_t port=0);
  void reset(uint8_t port=0);
  void CloseLED(void);
  void OpenLED(void);
  uint8_t readAnalog(void);

  
private:
	WeOneWire _WePotentiomter;
    volatile uint8_t  _Sensor1;
};

#endif

