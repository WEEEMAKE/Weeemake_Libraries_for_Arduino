
#ifndef WeIRAvoidSensor_H
#define WeIRAvoidSensor_H


#include "WePort.h"


class WeIRAvoidSensor
{
public:

  WeIRAvoidSensor(uint8_t port=0);
  void reset(uint8_t port=0);

  uint8_t isObstacle(void);
  void setColor1(uint8_t red, uint8_t green, uint8_t blue);
  void setColor2(uint8_t red, uint8_t green, uint8_t blue);
  void setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);
  void RGBShow(void);
  void LeftLED_ON(void);
  void LeftLED_OFF(void);
  void RightLED_ON(void);
  void RightLED_OFF(void);
  void setLed(uint8_t index, bool on);

private:
  void setLed(uint8_t);
	WeOneWire _WeIRAvoidSensor;
    volatile uint8_t  _Sensor_data;
	volatile uint8_t  _Led_data=0;
	volatile uint8_t  _RGB1_data[3]={0};
	volatile uint8_t  _RGB2_data[3]={0};
};

#endif

