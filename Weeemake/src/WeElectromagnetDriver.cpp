#include "WeElectromagnetDriver.h"

WeElectromagnetDriver::WeElectromagnetDriver(uint8_t port)
{
    reset(port);
}

void WeElectromagnetDriver::reset(uint8_t port)
{   
    _ElectromagnetDriver.reset(port);   
}

void WeElectromagnetDriver::setStatus(uint8_t index, bool isOn)
{
    _ElectromagnetDriver.reset();
    _ElectromagnetDriver.write_byte(0x02);
    _ElectromagnetDriver.reset();
    _ElectromagnetDriver.write_byte(index);
    _ElectromagnetDriver.write_byte(isOn);
    delayMicroseconds(10);
}