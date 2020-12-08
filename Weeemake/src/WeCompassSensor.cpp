#include "WeCompassSensor.h"


WeCompassSensor::WeCompassSensor(uint8_t port)
{
  _WeCompassSensor.reset(port);
}
void WeCompassSensor::reset(uint8_t port)
{
  _WeCompassSensor.reset(port);
}


void  WeCompassSensor::update(void)
{
  if(_WeCompassSensor.reset()!=0)
		  return ;
	  _WeCompassSensor.write_byte(0x02);
	  _WeCompassSensor.respond();
	  for(int i=0;i<6;i++)
	  {
		i2cData[i]=_WeCompassSensor.read_byte();
	  }
  
  head_X = ( (i2cData[0] << 8) | i2cData[1] );
  head_Y = ( (i2cData[2] << 8) | i2cData[3] );
  head_Z = ( (i2cData[4] << 8) | i2cData[5] );  
  
}

int16_t  WeCompassSensor::getHeadS(void)
{
  head_S=head_X-90;
  if(head_S<0) head_S=360+head_S;
  return head_S;
}
int16_t  WeCompassSensor::getHeadX(void)
{
  return head_X;
}
int16_t  WeCompassSensor::getHeadY(void)
{
  return head_Y;
}
int16_t  WeCompassSensor::getHeadZ(void)
{
  return head_Z;
}
int16_t  WeCompassSensor::getIntensityX(void)
{
   if(_WeCompassSensor.reset()!=0)
		  return head_X;
   _WeCompassSensor.write_byte(0x05);
   _WeCompassSensor.respond();	  
   i2cData[0]=_WeCompassSensor.read_byte();
   i2cData[1]=_WeCompassSensor.read_byte();
   head_X = ( (i2cData[0] << 8) | i2cData[1] );
   return head_X;
}
int16_t  WeCompassSensor::getIntensityY(void)
{
   if(_WeCompassSensor.reset()!=0)
		  return head_Y;
   _WeCompassSensor.write_byte(0x06);
   _WeCompassSensor.respond();	  
   i2cData[2]=_WeCompassSensor.read_byte();
   i2cData[3]=_WeCompassSensor.read_byte();
   head_Y = ( (i2cData[2] << 8) | i2cData[3] );
   return head_Y;
}

int16_t  WeCompassSensor::getIntensityZ(void)
{
   if(_WeCompassSensor.reset()!=0)
		  return head_Z;
   _WeCompassSensor.write_byte(0x07);
   _WeCompassSensor.respond();	  
   i2cData[4]=_WeCompassSensor.read_byte();
   i2cData[5]=_WeCompassSensor.read_byte();
   head_Z = ( (i2cData[4] << 8) | i2cData[5] );
   return head_Z;
}


int16_t WeCompassSensor::readValue(uint8_t index)
{
  update();
  switch(index){
    case 0: return getHeadS();
    case 1: return getHeadY();
  }
  return getHeadZ();
}

