
#ifndef WeRGBLED_RJ_H
#define WeRGBLED_RJ_H


#include "WePort.h"


class WeRGBLED_RJ
{
public:

  WeRGBLED_RJ(uint8_t port=0);
  void reset(uint8_t port=0);

  void setColor(uint8_t index,uint8_t red, uint8_t green, uint8_t blue);
  void RGBShow(void);
  void show();
  void setColor_j(uint8_t index,uint8_t red, uint8_t green, uint8_t blue);

  
private:
	WeOneWire _WeRGBLED_RJ;
	volatile uint8_t  _5RGB_data[15]={0};

};

#endif

