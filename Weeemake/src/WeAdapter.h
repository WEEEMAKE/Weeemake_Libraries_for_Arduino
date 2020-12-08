
#ifndef _WeAdapter_H
#define _WeAdapter_H

#include "WePort.h"

class WeAdapter
{
public:

  WeAdapter(uint8_t port=0);
  void reset(uint8_t port=0);
  void digitalWrite(uint8_t pin,uint8_t val);
  bool digitalRead(uint8_t pin);
  uint8_t analogRead(uint8_t pin);
  void write(uint8_t pin, uint8_t angle);
  void RGBshow(uint8_t pin, uint8_t index,uint8_t red, uint8_t green, uint8_t blue);
  void RGBshow(uint8_t pin, uint8_t index,uint32_t color);
  float readTemperature(uint8_t pin);
  
private:
   WeOneWire _WeAdapter;
   uint8_t s1,s2;
   float temperature;
};

#endif

