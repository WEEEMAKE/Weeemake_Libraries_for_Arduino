
#ifndef WePM25Sensor_H
#define WePM25Sensor_H


#include "WePort.h"


class WePM25Sensor
{
public:

  WePM25Sensor(uint8_t port=0);
  void reset(uint8_t port=0);

  uint16_t readPm1_0Concentration(void);    //PM1.0 ug/m^3
  uint16_t readPm2_5Concentration(void);    //PM2.5 ug/m^3
  uint16_t readPm10Concentration(void);     //PM10 ug/m^3
  uint16_t read0_3NumIn100ml(void);         //0.1L空气中直径在0.3um的颗粒物个数
  uint16_t read0_5NumIn100ml(void);         //0.1L空气中直径在0.5um的颗粒物个数
  uint16_t read1_0NumIn100ml(void);         //0.1L空气中直径在1.0um的颗粒物个数
  uint16_t read2_5NumIn100ml(void);         //0.1L空气中直径在2.5um的颗粒物个数
  uint16_t read5_0NumIn100ml(void);         //0.1L空气中直径在5.0um的颗粒物个数
  uint16_t read10NumIn100ml(void);          //0.1L空气中直径在10um的颗粒物个数
  void setFanLaser(bool isOn);
  
private:
	WeOneWire _WePM25Sensor;
  volatile uint16_t  _Sensor_data1;
  volatile uint8_t  _Sensor_data2;
};

#endif

