
#ifndef _WeLimitSwitch_H
#define _WeLimitSwitch_H

#include "WePort.h"

class WeLimitSwitch
{
public:

  WeLimitSwitch(uint8_t port=0);
  void reset(uint8_t port);
  bool read(void);
  
 private:
	uint8_t _Sensorpin;

};

#endif

