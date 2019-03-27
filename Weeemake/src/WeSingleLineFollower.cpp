#include "WeSingleLineFollower.h"

WeSingleLineFollower::WeSingleLineFollower(uint8_t port)
: WeSensor(port)
{
}

uint16_t WeSingleLineFollower::read(void)
{
   return 1023 - analogRead(_SensorPin);
}
