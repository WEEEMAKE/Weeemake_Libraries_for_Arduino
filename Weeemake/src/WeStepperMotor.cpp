#include "WeStepperMotor.h"

WeStepperMotor::WeStepperMotor(uint8_t port)
{
    _WeStepperMotor.reset(port);	
    pin=port;
}
void WeStepperMotor::reset(uint8_t port)
{
	_WeStepperMotor.reset(port);	
}

void WeStepperMotor::setMicroStep(uint8_t value)
{
     if(_WeStepperMotor.reset()!=0)
	   return;
	 _WeStepperMotor.write_byte(0x02);
     if(_WeStepperMotor.reset()!=0)
	   return;
     _WeStepperMotor.write_byte(value);
}
void WeStepperMotor::setSpeed(uint8_t speed)
{
    if(speed>255)  speed=255;
	if(_WeStepperMotor.reset()!=0)
	   return;
	_WeStepperMotor.write_byte(0x03);
	if(_WeStepperMotor.reset()!=0)
	   return;
	_WeStepperMotor.write_byte((uint8_t)speed);
}
void WeStepperMotor::moveTo(long value)
{
     if(last_value==value)
	return;
	if(_WeStepperMotor.reset()!=0)
	   return;
	_WeStepperMotor.write_byte(0x05);
	if(_WeStepperMotor.reset()!=0)
	   return;
	_WeStepperMotor.write_byte((uint8_t)value);
	_WeStepperMotor.write_byte((uint8_t)(value>>8));
	_WeStepperMotor.write_byte((uint8_t)(value>>16));
	_WeStepperMotor.write_byte((uint8_t)(value>>24));
	last_value=value;
	
}

void WeStepperMotor::move(long value)
{      
	if(_WeStepperMotor.reset()!=0)
	   return;
	_WeStepperMotor.write_byte(0x04);
	if(_WeStepperMotor.reset()!=0)
	   return;
	_WeStepperMotor.write_byte((uint8_t)value);
	_WeStepperMotor.write_byte((uint8_t)(value>>8));
	_WeStepperMotor.write_byte((uint8_t)(value>>16));
	_WeStepperMotor.write_byte((uint8_t)(value>>24));
}
void WeStepperMotor::setPositionOrigin(void)
{
  if(_WeStepperMotor.reset()!=0)
	   return;
  _WeStepperMotor.write_byte(0x06);	
}

void WeStepperMotor::stop(void)
{  
	if(_WeStepperMotor.reset()!=0)
	   return;
	_WeStepperMotor.write_byte(0x07);	
}
void WeStepperMotor::enableInfo(void)
{
	if(_WeStepperMotor.reset()!=0)
	return;
	_WeStepperMotor.write_byte(0x08);	

}
void WeStepperMotor::run(void)
{
	if(_WeStepperMotor.reset()!=0)
	return;
	_WeStepperMotor.write_byte(0x09);	

}
bool WeStepperMotor::isComplete(void)
{
    pinMode(pin, INPUT);
    return (digitalRead(pin));
}



