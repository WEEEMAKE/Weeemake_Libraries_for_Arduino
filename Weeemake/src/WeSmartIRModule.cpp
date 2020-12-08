#include "WeSmartIRModule.h"

WeSmartIRModule::WeSmartIRModule(uint8_t port)
{
  _WeSmartIRModule.reset(port);
}

void WeSmartIRModule::reset(uint8_t port)
{
  _WeSmartIRModule.reset(port);
}

void WeSmartIRModule::receiver(uint8_t num)
{
  if(_WeSmartIRModule.reset()!=0)
    return ;
  _WeSmartIRModule.write_byte(0x02);
  if(_WeSmartIRModule.reset()!=0)
    return ;
  _WeSmartIRModule.write_byte(num);
  delay(10);
}

void WeSmartIRModule::send(uint8_t num)
{
  if(_WeSmartIRModule.reset()!=0)
    return ;
  _WeSmartIRModule.write_byte(0x03);
  if(_WeSmartIRModule.reset()!=0)
    return ;
  _WeSmartIRModule.write_byte(num);
  delay(10);
}
