#ifndef WeLEDLineFollower_H
#define WeLEDLineFollower_H

#include "WePort.h"

class WeLEDLineFollower
{
public:
  WeLEDLineFollower(uint8_t port=0);
  void reset(uint8_t port=0);

  uint16_t readSensor(void);
  void openLED(void);
  void closeLED(void);
  void showLED(bool);

private:
	WeOneWire _WeLEDLineFollower;
    //volatile uint8_t  _Sensor;
};

#endif