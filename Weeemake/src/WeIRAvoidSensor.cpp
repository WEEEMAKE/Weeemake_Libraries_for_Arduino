#include "WeIRAvoidSensor.h"


WeIRAvoidSensor::WeIRAvoidSensor(uint8_t port)
{
  _WeIRAvoidSensor.reset(port);
}
void WeIRAvoidSensor::reset(uint8_t port)
{
  _WeIRAvoidSensor.reset(port);
}

uint8_t WeIRAvoidSensor::isObstacle(void)
{   
   if (_WeIRAvoidSensor.reset()!=0)
   	return 0;
   _WeIRAvoidSensor.write_byte(0x02);
   _WeIRAvoidSensor.respond();
   _Sensor_data=_WeIRAvoidSensor.read_byte();	
   delayMicroseconds(9000);
   return _Sensor_data;
}

void WeIRAvoidSensor::setColor1(uint8_t red, uint8_t green, uint8_t blue)
{
  _RGB1_data[0]=red;
  _RGB1_data[1]=green;
  _RGB1_data[2]=blue;
  RGBShow();
}
void WeIRAvoidSensor::setColor2(uint8_t red, uint8_t green, uint8_t blue)
{
  _RGB2_data[0]=red;
  _RGB2_data[1]=green;
  _RGB2_data[2]=blue;
  RGBShow();
}
void WeIRAvoidSensor::setColor(uint8_t index,uint32_t color)
{
  setColor(index, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
}
void WeIRAvoidSensor::setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
{
  if(index & 1){
    _RGB1_data[0]=red;
    _RGB1_data[1]=green;
    _RGB1_data[2]=blue;
  }
  if(index & 2){
    _RGB2_data[0]=red;
    _RGB2_data[1]=green;
    _RGB2_data[2]=blue;
  }
  if(index & 3){
    RGBShow();
  }
}
void WeIRAvoidSensor::RGBShow(void)
{
   if (_WeIRAvoidSensor.reset()!=0)
   	return;
  _WeIRAvoidSensor.write_byte(0x03);
  if (_WeIRAvoidSensor.reset()!=0)
   	return;
  _WeIRAvoidSensor.write_byte(_RGB1_data[0]);
  _WeIRAvoidSensor.write_byte(_RGB1_data[1]);
  _WeIRAvoidSensor.write_byte(_RGB1_data[2]);
  _WeIRAvoidSensor.write_byte(_RGB2_data[0]);
  _WeIRAvoidSensor.write_byte(_RGB2_data[1]);
  _WeIRAvoidSensor.write_byte(_RGB2_data[2]);
}

void WeIRAvoidSensor::setLed(uint8_t value)
{
    if(_WeIRAvoidSensor.reset())
      return;
    _WeIRAvoidSensor.write_byte(0x04);
    if(_WeIRAvoidSensor.reset())
      return;
    _Led_data = value;
    _WeIRAvoidSensor.write_byte(_Led_data);
}

void WeIRAvoidSensor::setLed(uint8_t index, bool on)
{
  if(index & 1){
    if(on){
      RightLED_ON();
    }else{
      RightLED_OFF();
    }
  }
  if(index & 2){
    if(on){
      LeftLED_ON();
    }else{
      LeftLED_OFF();
    }
  }
}

 void WeIRAvoidSensor::RightLED_ON(void)
 {
    setLed(_Led_data | 1);
 }
 void WeIRAvoidSensor::RightLED_OFF(void)
 {
    setLed(_Led_data & ~1);
 }
 void WeIRAvoidSensor::LeftLED_ON(void)
 {
    setLed(_Led_data | 2);
 }
 void WeIRAvoidSensor::LeftLED_OFF(void)
 {
    setLed(_Led_data & ~2);
 }
