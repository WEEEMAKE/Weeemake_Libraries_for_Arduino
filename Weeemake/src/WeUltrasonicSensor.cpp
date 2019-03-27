#include "WeUltrasonicSensor.h"


WeUltrasonicSensor::WeUltrasonicSensor(uint8_t port)
{
  _WeUltrasonicSensor.reset(port);
}
void WeUltrasonicSensor::reset(uint8_t port)
{
  _WeUltrasonicSensor.reset(port);
}


double WeUltrasonicSensor::distanceCm(void)
{
	uint16_t distance=0;
   if (_WeUltrasonicSensor.reset()!=0)
   	return 500;
   _WeUltrasonicSensor.write_byte(0x02);
   _WeUltrasonicSensor.respond();
   _Sensor_data1=_WeUltrasonicSensor.read_byte();
   _Sensor_data2=_WeUltrasonicSensor.read_byte();	
   distance=((uint16_t)_Sensor_data2<<8)|((uint16_t)_Sensor_data1);    
   if (((double)distance/17.57)>500)
   	return 500;
   else
   	return ((double)distance/17.57);    
}

void WeUltrasonicSensor::setColor1(uint8_t red, uint8_t green, uint8_t blue)
{
  _RGB1_data[0]=red;
  _RGB1_data[1]=green;
  _RGB1_data[2]=blue;
  RGBShow();
}
void WeUltrasonicSensor::setColor2(uint8_t red, uint8_t green, uint8_t blue)
{
  _RGB2_data[0]=red;
  _RGB2_data[1]=green;
  _RGB2_data[2]=blue;
  RGBShow();
}
void WeUltrasonicSensor::setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
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
void WeUltrasonicSensor::RGBShow(void)
{
   if (_WeUltrasonicSensor.reset()!=0)
   	return;
  _WeUltrasonicSensor.write_byte(0x03);
  if (_WeUltrasonicSensor.reset()!=0)
   	return;
  _WeUltrasonicSensor.write_byte(_RGB1_data[0]);
  _WeUltrasonicSensor.write_byte(_RGB1_data[1]);
  _WeUltrasonicSensor.write_byte(_RGB1_data[2]);
  _WeUltrasonicSensor.write_byte(_RGB2_data[0]);
  _WeUltrasonicSensor.write_byte(_RGB2_data[1]);
  _WeUltrasonicSensor.write_byte(_RGB2_data[2]);
}

void WeUltrasonicSensor::setLed(uint8_t index, bool isOn)
{
	index &= 3;
	if(0 == index)return;
	if(isOn){
		_Led_data |= index;
	}else{
		_Led_data &= ~index;
	}
	if(_WeUltrasonicSensor.reset())return;
	_WeUltrasonicSensor.write_byte(0x04);
	if(_WeUltrasonicSensor.reset())return;
	_WeUltrasonicSensor.write_byte(_Led_data);
}

void WeUltrasonicSensor::RightLED_ON(void)
 {
    setLed(1, true);
 }
 void WeUltrasonicSensor::RightLED_OFF(void)
 {
    setLed(1, false);
 }
 void WeUltrasonicSensor::LeftLED_ON(void)
 {
    setLed(2, true);
 }
 void WeUltrasonicSensor::LeftLED_OFF(void)
 {
    setLed(2, false);
 }


