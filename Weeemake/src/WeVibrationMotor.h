#ifndef _WeVibrationMotor_H
#define _WeVibrationMotor_H

#include "WePort.h"

class WeVibrationMotor
{
public:

  WeVibrationMotor(uint8_t port=0); 
  void reset(uint8_t port=0);
  void run(uint8_t speed);
  void run(void);
  void stop(void);

  
private:
	WeOneWire _WeVibrationMotor;
};

#endif

