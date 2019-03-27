#include "WeWaterAtomizer.h"

WeWaterAtomizer::WeWaterAtomizer(uint8_t port)
{
  _WeWaterAtomizer.reset(port);
}
void WeWaterAtomizer::reset(uint8_t port)
{
  _WeWaterAtomizer.reset(port);
}

void WeWaterAtomizer::start(void)
{
   setRun(true);
}
void WeWaterAtomizer::stop(void)
{
   setRun(false);
}

void WeWaterAtomizer::setRun(bool isOn)
{
	if(_WeWaterAtomizer.reset())return;
   _WeWaterAtomizer.write_byte(isOn ? 2 : 3);
}





