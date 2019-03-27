#ifndef _WeRelay_H
#define _WeRelay_H

#include "WePort.h"

class WeRelay
{
public:

  WeRelay(uint8_t port=0); 
  void reset(uint8_t port=0);

  void openNC(void);
  void closeNC(void);
  void setNC(bool isOn);

  
private:
	WeOneWire _WeRelay;
};

#endif

