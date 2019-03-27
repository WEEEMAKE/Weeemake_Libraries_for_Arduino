
#ifndef WeSingleLineFollower_H
#define WeSingleLineFollower_H

#include "WePort.h"

class WeSingleLineFollower : public WeSensor
{
public:
  WeSingleLineFollower(uint8_t=0);
  uint16_t read(void);
};

#endif

