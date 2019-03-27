#include "WePM25Sensor.h"


WePM25Sensor::WePM25Sensor(uint8_t port)
{
  _WePM25Sensor.reset(port);
}
void WePM25Sensor::reset(uint8_t port)
{
  _WePM25Sensor.reset(port);
}
void WePM25Sensor::setFanLaser(bool isOn)             //设置PM2.5模块上面的风扇和激光头开关
{
  if(_WePM25Sensor.reset())return;
  _WePM25Sensor.write_byte(0x02);
  if(_WePM25Sensor.reset())return;
  _WePM25Sensor.write_byte(isOn);
}

uint16_t WePM25Sensor::readPm1_0Concentration(void)    //PM1.0 ug/m^3
{
  uint16_t SensorData=0;
  if (_WePM25Sensor.reset()!=0)
    return 0; 
  _WePM25Sensor.write_byte(0x03);
  _WePM25Sensor.respond();
  _Sensor_data1=_WePM25Sensor.read_byte();
  _Sensor_data2=_WePM25Sensor.read_byte();
  SensorData=(uint16_t)(_Sensor_data1<<8|_Sensor_data2);
  return SensorData;
}
uint16_t WePM25Sensor::readPm2_5Concentration(void)    //PM2.5 ug/m^3
{
  uint16_t SensorData=0;
  if (_WePM25Sensor.reset()!=0)
    return 0;
  _WePM25Sensor.write_byte(0x04);
  _WePM25Sensor.respond();
  _Sensor_data1=_WePM25Sensor.read_byte();
  _Sensor_data2=_WePM25Sensor.read_byte();
  SensorData=(uint16_t)(_Sensor_data1<<8|_Sensor_data2);
  return SensorData;
}
uint16_t WePM25Sensor::readPm10Concentration(void)     //PM10 ug/m^3
{
  uint16_t SensorData=0;
  if (_WePM25Sensor.reset()!=0)
    return 0;
  _WePM25Sensor.write_byte(0x05);
  _WePM25Sensor.respond();
  _Sensor_data1=_WePM25Sensor.read_byte();
  _Sensor_data2=_WePM25Sensor.read_byte();
  SensorData=(uint16_t)(_Sensor_data1<<8|_Sensor_data2);
  return SensorData;
}
uint16_t WePM25Sensor::read0_3NumIn100ml(void)         //0.1L空气中直径在0.3um的颗粒物个数
{
  uint16_t SensorData=0;
  if (_WePM25Sensor.reset()!=0)
    return 0;
  _WePM25Sensor.write_byte(0x06);
  _WePM25Sensor.respond();
  _Sensor_data1=_WePM25Sensor.read_byte();
  _Sensor_data2=_WePM25Sensor.read_byte();
  SensorData=(uint16_t)(_Sensor_data1<<8|_Sensor_data2);
  return SensorData;
}
uint16_t WePM25Sensor::read0_5NumIn100ml(void)         //0.1L空气中直径在0.5um的颗粒物个数
{
  uint16_t SensorData=0;
  if (_WePM25Sensor.reset()!=0)
    return 0;
  _WePM25Sensor.write_byte(0x07);
  _WePM25Sensor.respond();
  _Sensor_data1=_WePM25Sensor.read_byte();
  _Sensor_data2=_WePM25Sensor.read_byte();
  SensorData=(uint16_t)(_Sensor_data1<<8|_Sensor_data2);
  return SensorData;
}
uint16_t WePM25Sensor::read1_0NumIn100ml(void)         //0.1L空气中直径在1.0um的颗粒物个数
{
  uint16_t SensorData=0;
  if (_WePM25Sensor.reset()!=0)
    return 0;
  _WePM25Sensor.write_byte(0x08);
  _WePM25Sensor.respond();
  _Sensor_data1=_WePM25Sensor.read_byte();
  _Sensor_data2=_WePM25Sensor.read_byte();
  SensorData=(uint16_t)(_Sensor_data1<<8|_Sensor_data2);
  return SensorData;
}
uint16_t WePM25Sensor::read2_5NumIn100ml(void)         //0.1L空气中直径在2.5um的颗粒物个数
{
  uint16_t SensorData=0;
  if (_WePM25Sensor.reset()!=0)
    return 0;
  _WePM25Sensor.write_byte(0x09);
  _WePM25Sensor.respond();
  _Sensor_data1=_WePM25Sensor.read_byte();
  _Sensor_data2=_WePM25Sensor.read_byte();
  SensorData=(uint16_t)(_Sensor_data1<<8|_Sensor_data2);
  return SensorData;
}
uint16_t WePM25Sensor::read5_0NumIn100ml(void)         //0.1L空气中直径在5.0um的颗粒物个数
{
  uint16_t SensorData=0;
  if (_WePM25Sensor.reset()!=0)
    return 0;
  _WePM25Sensor.write_byte(0x0a);
  _WePM25Sensor.respond();
  _Sensor_data1=_WePM25Sensor.read_byte();
  _Sensor_data2=_WePM25Sensor.read_byte();
  SensorData=(uint16_t)(_Sensor_data1<<8|_Sensor_data2);
  return SensorData;
}
uint16_t WePM25Sensor::read10NumIn100ml(void)          //0.1L空气中直径在10um的颗粒物个数
{
  uint16_t SensorData=0;
  if (_WePM25Sensor.reset()!=0)
    return 0;
  _WePM25Sensor.write_byte(0x0b);
  _WePM25Sensor.respond();
  _Sensor_data1=_WePM25Sensor.read_byte();
  _Sensor_data2=_WePM25Sensor.read_byte();
  SensorData=(uint16_t)(_Sensor_data1<<8|_Sensor_data2);
  return SensorData;
}



