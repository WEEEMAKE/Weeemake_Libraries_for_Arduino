#include "WeVibrationMotor.h"

WeVibrationMotor::WeVibrationMotor(uint8_t port)
{
    _WeVibrationMotor.reset(port);
}

void WeVibrationMotor::reset(uint8_t port)
{	
	_WeVibrationMotor.reset(port);	
}

void WeVibrationMotor::run(uint8_t speed)
{
     _WeVibrationMotor.reset();
	 _WeVibrationMotor.write_byte(0x03);
     _WeVibrationMotor.reset();
     _WeVibrationMotor.write_byte(speed);
     delay(1);
}

void WeVibrationMotor:: stop(void)
{
	_WeVibrationMotor.reset();
    _WeVibrationMotor.write_byte(0x04);
}
void WeVibrationMotor:: run(void)
{
	_WeVibrationMotor.reset();
    _WeVibrationMotor.write_byte(0x02);
}





