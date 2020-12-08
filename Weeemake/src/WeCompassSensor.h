#ifndef _WeCompassSensor_H
#define _WeCompassSensor_H

#include "WePort.h"

class WeCompassSensor
{
public:

  WeCompassSensor(uint8_t port=0);
  void reset(uint8_t port=0);
  void update(void);
  int16_t getHeadS(void);
  int16_t getHeadX(void);
  int16_t getHeadY(void);
  int16_t getHeadZ(void);
  int16_t getIntensityX(void);
  int16_t getIntensityY(void);
  int16_t getIntensityZ(void);

  int16_t readValue(uint8_t index);
  
private:
	WeOneWire _WeCompassSensor;
    int  head_X=0, head_Y=0, head_Z=0;
	int  head_S=0;
    uint8_t i2cData[6];
};

#endif

