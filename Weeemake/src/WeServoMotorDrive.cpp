#include "WeServoMotorDrive.h"


WeServoMotorDrive::WeServoMotorDrive(uint8_t port)
{
  _WeServoMotorDrive.reset(port);
}
void WeServoMotorDrive::reset(uint8_t port)
{
  _WeServoMotorDrive.reset(port);
}

void WeServoMotorDrive::write(uint8_t pin, uint8_t angle)
{
    if(_WeServoMotorDrive.reset()!=0)
       return ;
    _WeServoMotorDrive.write_byte(0x02);
    if(_WeServoMotorDrive.reset()!=0)
       return ;
	_WeServoMotorDrive.write_byte(pin);
	_WeServoMotorDrive.write_byte(angle);

}
void WeServoMotorDrive::RGBshow(uint8_t pin, uint8_t index,uint8_t red, uint8_t green, uint8_t blue)
{
	if(_WeServoMotorDrive.reset()!=0)
       return ;
    _WeServoMotorDrive.write_byte(0x03);
    if(_WeServoMotorDrive.reset()!=0)
       return ;
	_WeServoMotorDrive.write_byte(pin);
	_WeServoMotorDrive.write_byte(index);
	_WeServoMotorDrive.write_byte(red);
	_WeServoMotorDrive.write_byte(green);
	_WeServoMotorDrive.write_byte(blue);
	delayMicroseconds(2000);
}




