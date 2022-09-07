
#ifndef WeMultipleLineFollower_H
#define WeMultipleLineFollower_H

#include "WePort.h"

class WeMultipleLineFollower
{
public:

  WeMultipleLineFollower(uint8_t port=0);
  void reset(uint8_t port=0);

  void startRead(void);
  uint8_t readSensor1(void);
  uint8_t readSensor2(void);
  uint8_t readSensor3(void);
  uint8_t readSensor4(void);
  uint8_t readSensor5(void);
  
  uint8_t readSensor(void);

  
  void openLED(void);
  void closeLED(void);


  
private:
	WeOneWire _WeMultipleLineFollower;
	volatile uint8_t  _Sensor;
    volatile uint8_t  _Sensor1;
    volatile uint8_t  _Sensor2;
	volatile uint8_t  _Sensor3;
    volatile uint8_t  _Sensor4;
	volatile uint8_t  _Sensor5;

};

#endif

