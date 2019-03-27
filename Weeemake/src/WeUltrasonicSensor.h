
#ifndef WeUltrasonicSensor_H
#define WeUltrasonicSensor_H


#include "WePort.h"


class WeUltrasonicSensor
{
public:

  WeUltrasonicSensor(uint8_t port=0);
  void reset(uint8_t port=0);

  double distanceCm(void);
  void setColor1(uint8_t red, uint8_t green, uint8_t blue);
  void setColor2(uint8_t red, uint8_t green, uint8_t blue);
  void setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);
  void LeftLED_ON(void);
  void LeftLED_OFF(void);
  void RightLED_ON(void);
  void RightLED_OFF(void);
  void setLed(uint8_t index, bool isOn);
private:
  void RGBShow(void);



  
private:
	WeOneWire _WeUltrasonicSensor;
    volatile uint8_t  _Sensor_data1;
    volatile uint8_t  _Sensor_data2;
	volatile uint8_t  _RGB1_data[3]={0};
	volatile uint8_t  _RGB2_data[3]={0};
  volatile uint8_t  _Led_data=0;
};

#endif

