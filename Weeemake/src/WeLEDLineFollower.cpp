#include"WeLEDLineFollower.h"

WeLEDLineFollower::WeLEDLineFollower(uint8_t port)
{
  reset(port);
}
void WeLEDLineFollower::reset(uint8_t port)
{
	_WeLEDLineFollower.reset(port);
}

uint16_t WeLEDLineFollower::readSensor(void)
{
  if(_WeLEDLineFollower.reset()!=0)
    return 0;
  _WeLEDLineFollower.write_byte(0x02);
  _WeLEDLineFollower.respond();
  uint8_t value = _WeLEDLineFollower.read_byte();
  return uint16_t(value * 1023.0 / 255.0);
}

void WeLEDLineFollower::openLED(void)
{
	showLED(true);
}

void WeLEDLineFollower::closeLED(void)
{
	showLED(false);
}

void WeLEDLineFollower::showLED(bool isOn)
{
	if(_WeLEDLineFollower.reset())
		return;
	_WeLEDLineFollower.write_byte(isOn ? 3 : 4);
}