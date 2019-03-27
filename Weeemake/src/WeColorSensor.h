#ifndef _WeColorSensor_H
#define _WeColorSensor_H

#include "WePort.h"

class WeColorSensor
{
public:

  WeColorSensor(uint8_t port=0);
  void reset(uint8_t port=0);
  void readColorData(void);
  void whitebalance(void);
  uint16_t showRedData(void);
  uint16_t showGreenData(void);
  uint16_t showBlueData(void);
  uint16_t showColorData(void);
  void turnOnLight(void);
  void turnOffLight(void);
  void setLight(bool isOn);  
  uint16_t readValue(uint8_t type);
 
  
private:
	WeOneWire _WeColorSensor;
	 uint16_t Redvalue;
     uint16_t Greenvalue;
     uint16_t Bluevalue;
     uint16_t Colorvalue;
     bool wb_flag;
};

#endif

