#ifndef _WeStepperMotor_H
#define _WeStepperMotor_H

#include "WePort.h"

class WeStepperMotor
{
public:

  WeStepperMotor(uint8_t port=0); 
  void reset(uint8_t port=0);
  void setMicroStep(uint8_t value);
  void setSpeed(uint8_t speed);
  void moveTo(long value);
  void move(long value);
  void stop(void);
  void setPositionOrigin(void);
  void enableInfo(void);
  void run(void);
  bool isComplete(void);
private:
  WeOneWire _WeStepperMotor;
  long   last_value=0;
  uint8_t pin;
};

#endif

