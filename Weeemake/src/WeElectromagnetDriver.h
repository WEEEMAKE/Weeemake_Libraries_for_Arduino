#ifndef _WeElectromagnetDriver_H
#define _WeElectromagnetDriver_H

#include "WePort.h"

class WeElectromagnetDriver
{
public:
  WeElectromagnetDriver(uint8_t port=0); 
  void reset(uint8_t port=0);

  void setStatus(uint8_t index, bool isOn);

private:
	WeOneWire _ElectromagnetDriver;
};

#endif

